// Copyright 2018, Institute for Artificial Intelligence - University of Bremen
// Author: Patrick Kellmann

#pragma once

#include "CoreMinimal.h"
#include "MWControllerHandler.h"

/**
 * This class covers all functions that affect the wheels.
 */
class UBASECONTROLLERMW_API MWControllerWheelHandler : private MWControllerHandler
{
public:

	/*
	* Constructor of the handler.
	*
	* @param MWControllerComponent Owner of the handler.
	*/
	MWControllerWheelHandler(UMWControllerComponent* MWControllerComponent);

	/*
	* Destructor of the handler.
	*
	*/
	~MWControllerWheelHandler();

	/*
	* Calculates the distance between the wheels. This must not deviate too far due to the mathematical formulas.
	*
	* @return true if distance is correct, otherwise false.
	*/
	bool IsDistanceBetweenWheelsValid();

	/*
	* Calculates the distance between the wheels.
	*
	* @return Distances between the wheels (half of front to wheels, half of front to rear)
	*/
	TPair<float, float> CalcDistanceBetweenWheels();

	/*
	* Calculates the (mesh) wheeldiameter in centimeters (1 cm = 1 uu). Looks if size deviations exist.
	*
	* @return Wheeldiameter of the wheels.
	*/
	float CalcWheelDiameterInCentimeter();

	/*
	* Starts the calculations of the angular velocity of the wheels and the wheel rotation.
	*
	* @param Velocity The linear and angular velocities of the base.
	*/
	void SetupWheelsMovement(const FVector Velocity);

	

private:

	/*
	* Sets the linear velocites of the wheels.
	*
	* @param Velocity Velocites to set.
	*/
	void SetWheelsMovementVelocities(const FVector Velocity);

	/*
	* Sets the velocity (linear) to avoid problems.
	*
	* @param LongitudinalVelocity Velocity to set. 
	* @param Wheel Wheel. 
	*/
	FVector CalcLongitudinal(const FVector LongitudinalVelocity, const UStaticMeshComponent* Wheel);


	/*
	* Sets the velocity (linear) to avoid problems.
	*
	* @param TransversalVelocity Velocity to set. 
	* @param Wheel Wheel. 
	*/
	FVector CalcTransversal(const FVector TransversalVelocity, const UStaticMeshComponent* Wheel);

	/*
	TODO
	*/
	FVector CalcAngular(const FVector AngularVelocity, const UStaticMeshComponent * Wheel);


	/*
	TODO 
	*/
	void ShiftWheelsForAngularMovement(const FVector AngularVelocity, UStaticMeshComponent* Wheel);

	/*
	* Calculates the angular speed of the wheels.
	*
	* @param Velocity The velocity that is applied.
	*/
	void CalcWheelsAngularVelocity(const FVector Velocity);

	/*
	* Calculates the turning of the wheels.
	*
	*/
	void RotateWheels();
};
