#include "gnc.h"

gnc::GNCEngine::GNCEngine()
	: control_engine(0, 0, 0)
{

}

void gnc::GNCEngine::receive_target_packages(std::vector<TargetPackage> target_packages)
{
	// TODO: parse target packages
	return;
}