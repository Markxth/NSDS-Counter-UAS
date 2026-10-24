import cv2 as cv
from pathlib import Path
from ultralytics import YOLO
from time import monotonic

pt = "drone26n.pt"
forget_drone_after_this_time = 10.0 # seconds 

def drone_tracking(model_path, camera_index=0, takeoff_alt=0.2, conf=0.1):
    model = YOLO(model_path)
    cap = cv.VideoCapture(camera_index)
    if not cap.isOpened():
        raise IOError("Camera not accessible")

    width  = int(cap.get(cv.CAP_PROP_FRAME_WIDTH))
    height = int(cap.get(cv.CAP_PROP_FRAME_HEIGHT))

    # drone ID -> where and when we last saw that drone, e.g. {3: {"x": 120.0, "y": 85.5, "time": 1042.7}}
    last_seen = {}

    while True:
        ret, frame = cap.read()
        if not ret:
            break

        # TODO 
        # need lap package, currently use bytetrack as default, might use botsort depending on whether we want a better compatibility with moving camera
        results = model.track(frame, persist=True, verbose=False, conf=conf, tracker="bytetrack.yaml") 

        tracked = [] # handoff
        t = monotonic()

        if len(results[0].boxes) > 0:
            boxes     = results[0].boxes
            '''
            depreciated human detection
            mask = results[0].boxes.cls == 0 #mask 
            humans = results[0].boxes[mask] #get only humans
            for human in humans :
                x1, y1, x2, y2 = human.xyxy[0]
                cv.rectangle(frame, (int(x1), int(y1)), (int(x2), int(y2)), (0,255,0), 1)
                confidence = human.conf[0].item() #item() convers from tensor to float
                cv.putText(frame, f'human : confidence : {confidence:.2f}', (int(x1),int(y1)), cv.FONT_HERSHEY_SIMPLEX, 1, (0,255,0), 2)
            '''

            for drone in results[0].boxes:
                x1,y1,x2,y2 = drone.xyxy[0]
                confidence = drone.conf[0].item()

                # camera debug thingy, can delete if needed
                label = f'drone {int(drone.id[0])}' if drone.id is not None else 'drone (unconfirmed)'
                cv.rectangle(frame, (int(x1), int(y1)), (int(x2), int(y2)), (0,255,0), 1)
                cv.putText(frame, f'{label} : confidence : {confidence:.2f}', (int(x1),int(y1)), cv.FONT_HERSHEY_SIMPLEX, 1, (0,255,0), 2)

                # Unconfirmed drones have no ID, so id and velocity stay None for them, requested by GNC to have unconfirmed sent 
                confirmed = drone.id is not None
                tid = int(drone.id[0]) if confirmed else None
                current_x, current_y = drone.xywh[0][:2].tolist()

                velocity_x = velocity_y = None # placeholder float for velocity

                if confirmed and tid in last_seen:
                    previous = last_seen[tid]
                    dt = t - previous["time"]
                    if dt > 0:
                        velocity_x = (current_x - previous["x"]) / dt
                        velocity_y = (current_y - previous["y"]) / dt

                if confirmed:
                    last_seen[tid] = {"x": current_x, "y": current_y, "time": t} # re-initalize the "screenshot": last seen id = thing that you see here
                tracked.append({"id":tid, "confirmed": confirmed, "current_x":current_x, "current_y":current_y, "velocity_x": velocity_x, "velocity_y": velocity_y,
                               "confidence": confidence})
                '''
                GNC Usage in python:
                for drone in tracked:
                    print(drone["id'], drone["velocity_x"]) etc
                
                '''
        else:
            pass

        # forget drones we haven't seen recently
        last_seen = {tid: seen for tid, seen in last_seen.items() if t - seen["time"] < forget_drone_after_this_time}

        yield tracked

        cv.imshow("tracking", frame)
        if cv.waitKey(1) & 0xFF == ord('q'):
            break

    cap.release()
    cv.destroyAllWindows()

# aim(Path(__file__).parent.parent / "yolo26n.pt")
# aim(Path(__file__).parent.parent / "drone26n.pt")
if __name__ == "__main__":
    for tracked in drone_tracking(Path(__file__).parent.parent / pt):
        print(tracked)
