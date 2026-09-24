import math

import numpy as np
import numpy.typing as npt

from coordinate_conversions import rae_xyz, xyzv_raer

class UKF:
    def __init__(self, initial_state, initial_covariance, process_noise):
        """Initialize UKF class members.
        
        Keyword Args:
            initial_state -- the initial statevector of the target
            initial_covariance -- the covariance of the initial statevector
            process_noie -- the estimated process noise of the initial statevector
        """
        self._statevector = np.asarray(initial_state, dtype=float)
        self._covariance = np.asarray(initial_covariance, dtype=float)
        self._process_noise = np.asarray(process_noise, dtype=float)

    ###################################################
    # Kalman Utility

    def _generate_sigma_points(xhat, covariance):
        """Return a collection of sigma points generated from a statevector and the covariance of the statevector.
        Also returns the weights associated with the sigma points.
        
        Sigma points are deterministic samples that represent the mean and covariance of a state estimate.
        Sigma points can be propagated through nonlinear functions to approximate the resulting mean and covariance.

        Keyword Args:
            xhat -- a statevector, could be current or predicted
            covariance -- the covariance of the given statevector
        """

        xhat = np.asarray(xhat, dtype=float)        # Ensure xhat is an np array
        P = np.asarray(covariance, dtype=float)     # Ensure covariance is an np array

        n = xhat.size
        point_count = 2*n + 1

        # UKF Scaling Parameters
        alpha = 1e-3        # NOTE: controls the spread of sigma points around the mean
        beta = 2.0          # NOTE: adjusts the central point's covariance to account for prior knowledge
        kappa = 0.0         # NOTE: secondary scaling parameter that affects the spread based on the state dimension

        alpha_sq = alpha*alpha

        # λ = α^{2} (n +  κ) - n
        lam = alpha_sq * (n + kappa) - n
        L = np.linalg.cholesky((n + lam) * P)

        # Create sigma points from generated offsets
        sigma_points = [xhat]
        for i in range(n):
            offset = L[:, i]

            sigma_points.append(xhat + offset)
            sigma_points.append(xhat - offset)

        # Calculate sigma point weights
        mean_weights = np.full(point_count, 1.0 / (2.0 * (n + lam)))
        covariance_weights = mean_weights.copy()

        mean_weights[0] = lam / (n + lam)
        covariance_weights[0] = mean_weights[0] + (1.0 - alpha_sq) + beta

        return sigma_points, mean_weights, covariance_weights

    def _generate_gain(predicted, predicted_covariance, measurement_covariance):
        """Returns the kalman gain, predicted measurement, and uncertainty of the predicted state, calculated from
        the current prediction, the covariance of that prediction, and the covariance of the measurement.

        The Kalman Gain is used as a sort of weighting between the prediction and the measurement. Because both the
        predicted state and the measured state have some uncertainty to them, neither can be fully trusted and so the most
        reliable method is to find some average of the two. Because the uncertainties will differ, taking an evenly weighted
        average is naive and it is instead better to analyze the uncertainties of each component and generate a weight from
        those uncertainties. The Kalman Gain returned by this method is a weighting applied to balance the uncertainties of
        the prediction and the measurement.

        Keyword Args:
            predicted -- the predicted statevector
            predicted_covariance -- the covariance of the predicted statevector
            measurement_covariance -- the covariance of the measurement
        """
        n = predicted.size
        point_count = 2*n + 1

        sigma_points, mean_weights, covariance_weights = UKF._generate_sigma_points(predicted, predicted_covariance)

        # Convert sigma points to measurement space
        measurement_points = np.asarray([
            xyzv_raer(point) for point in sigma_points
        ])

        # Create a predicted measurement from the weighted average of the sigma points in measurement space
        z_predicted = np.sum(
            mean_weights[:, None] * measurement_points,
            axis = 0
        )

        # Get the deviataions of the sigma points in measurement space
        dz = measurement_points - z_predicted

        # Get the deviations of the sigma points in state space
        dx = sigma_points - predicted

        R = np.asarray(measurement_covariance, dtype=float)
        S = R.copy()

        # Create the state measurement cross covariance
        P_xz = np.zeros((n, z_predicted.size))
        for i in range(point_count):
            S += covariance_weights[i] * np.outer(dz[i], dz[i])
            P_xz += covariance_weights[i] * np.outer(dx[i], dz[i])

        # Get the kalman gain
        K = np.linalg.solve(S, P_xz.T).T

        return K, z_predicted, S

    ###################################################
    # Kalman Core

    def _predict_ukf(current, covariance, process_noise, delta_time):
        """Returns a predicted statevector and the covariance of the prediction.

        Sigma points are generated from the current state estimate and propagated through the
        (constant velocity) motion model. The propagated points are used to calculate the predicted
        state mean and covariance.

        Keyword Args:
            current -- the current statevector estimate
            covariance -- the current state covariance matrix
            process_noise -- the process noise covariance matrix
            delta_time -- the time step between statevector prediction
        """
        sigma_points, mean_weights, covariance_weights = UKF._generate_sigma_points(current, covariance)

        F = np.array([
            [1, 0, 0, delta_time, 0, 0],
            [0, 1, 0, 0, delta_time, 0],
            [0, 0, 1, 0, 0, delta_time],
            [0, 0, 0, 1, 0, 0],
            [0, 0, 0, 0, 1, 0],
            [0, 0, 0, 0, 0, 1]
        ], dtype=float)
        Q = np.asarray(process_noise, dtype=float)

        # Propagate each sigma point through the motion model
        propagated_points = np.asarray([
            F @ point for point in sigma_points
        ])

        # Predicted state mean
        predicted = np.sum(
            mean_weights[:, None] * propagated_points,
            axis=0
        )

        # Predicted state covariance
        predicted_covariance = Q.copy()

        for i in range(2 * len(current) + 1):
            deviation = propagated_points[i] - predicted
            predicted_covariance += covariance_weights[i] * np.outer(deviation, deviation)

        return predicted, predicted_covariance

    def _update_ukf(predicted, predicted_covariance, measurement, measurement_covariance):
        """Returns an updated statevector and a covariance for the updated statevector based on the predicted statevector,
        the measurement, and the covariances of each.
        
        Keyword Args:
            predicted -- the predicted statevector
            predicted_covariance -- the covariance of the predicted statevector
            measurement -- the measured statevector
            measurement_covariance -- the covariance of the measurement
        """
        K, z_predicted, S = UKF._generate_gain(predicted, predicted_covariance, measurement_covariance)

        # Calculate Innovation from measurement and the predicted measurement
        innovation = measurement - z_predicted

        # Wrap the azimuth and elevation components of the innovation to [-1, 1]
        innovation[1] = (innovation[1] + np.pi) % (2.0 * np.pi) - np.pi
        innovation[2] = (innovation[2] + np.pi) % (2.0 * np.pi) - np.pi

        updated = predicted + K @ innovation
        updated_covariance = predicted_covariance - K @ S @ K.T

        return updated, updated_covariance

    ###################################################
    # Public Interface

    def update(self, measurement, measurement_covariance, delta_time):
        """Returns an updated statevector and covariance from the next measurement and the
        delta time. This updated statevector takes into consideration the computed prediction for 
        the statevector, as well as the measured statevector, and the uncertainties of both in
        order to reach a middle ground that is believed to be more accurate than either the prediction
        or the measurement.

        Keyword Args:
            measurement -- the measured RAER position of the target
            measurement_covariance -- the covariance of the measurement, derived from infomration about the sensors
            delta_time -- the time step between consecutive measurements
        """
        # Predict the state and covariance
        predicted_state, predicted_covariance = UKF._predict_ukf(
            self._statevector,
            self._covariance,
            self._process_noise,
            delta_time
        )

        # Correct the prediction using the measurement
        updated_state, updated_covariance = UKF._update_ukf(
            predicted_state,
            predicted_covariance,
            measurement,
            measurement_covariance
        )

        self._statevector = updated_state
        self._covariance = updated_covariance

        return self._statevector, self._covariance

    ###################################################
    # Public Utilities

    def generate_process_noise(delta_time, acceleration_noise_intensity):
        """Returns a process noise matrix that is generated from a time step and a guess
        at the affects of the UKF model not accounting for acceleration. The acceleration
        noise intensity should be adjusted to make the model more accurate.

        Keyword Args:
            delta_time -- the time step between consecutive measurements
            acceleration_noise_intensity -- an parameter controlling how strong the affects of acceleration are estimated to be
        """
        dt = delta_time
        q = acceleration_noise_intensity

        position_noise = (dt**3) / 3.0
        position_velocity_noise = (dt**2) / 2.0
        velocity_noise = dt

        Q = q * np.block([
            [position_noise * np.eye(3), position_velocity_noise * np.eye(3)],
            [position_velocity_noise * np.eye(3), velocity_noise * np.eye(3)]
        ])

        return Q

# TESTING
# NOTE & TODO: these values are made up in order to test the functionality of UKF. These values and the ones
# used in UKF WILL need to change as test data becomes available.
initial_statevector = np.array([
    100.0, 0.0, 0.0,                # x, y, z
    10.0, 0.0, 0.0                  # vx, vy, vz
])

initial_covariance = np.diag([
    25.0, 25.0, 25.0,
    4.0, 4.0, 4.0
])

delta_time = 0.5
acceleration_noise_intensity = 1.0

process_noise = UKF.generate_process_noise(delta_time, acceleration_noise_intensity)

ukf = UKF(initial_statevector, initial_covariance, process_noise)

z1 = np.array([
    102.0,      # range
    0.01,       # azimuth
    0.005,      # elevation
    9.5,        # range rate
])

z1_covariance = np.diag([
    4.0, 0.0001, 0.0001, 0.25 
])

updated_state, updated_covariance = ukf.update(z1, z1_covariance, delta_time)
print(f'Updated State: {updated_state}\nUpdated Covariance: {updated_covariance}')