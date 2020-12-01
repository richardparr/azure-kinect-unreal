// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HAL/Runnable.h"
#include "HAL/RunnableThread.h"

class AzureKinectDevice;

DECLARE_LOG_CATEGORY_EXTERN(AzureKinectThreadLog, Log, All);

/**
 * A thread that is used to capture the Azure Kinect device's body frame data.
 *
 * @see Multi-Threading in UE4 https://wiki.unrealengine.com/Multi-Threading:_How_to_Create_Threads_in_UE4
 */
class AZUREKINECTUNREAL_API FAzureKinectThread : public FRunnable
{
public:
	/**
	 * Ctor
	 *
	 * @param Device A pointer to the Azure Kinect device that starts this thread 
	 * and which will be used to call the capture body frame function.
	 */
	FAzureKinectThread(AzureKinectDevice *Device);
	/** Destructor */
	~FAzureKinectThread();

	/** Initializes the thread with the given Device. */
	static FAzureKinectThread *InitPolling(AzureKinectDevice *Device);

	/** Completes the execution of the thread */
	static void Shutdown(AzureKinectDevice *Device);
	
	/** Stops the thread and waits for its completion. */
	void EnsureCompletion();

	// Begin FRunnable interface
	virtual bool Init();
	virtual uint32 Run();
	virtual void Stop();
	// End FRunnable interface

private:
	/** A singleton instance array. */
	static TArray<FAzureKinectThread *> Instances;

	/** Thread to run this Runnable object. */
	FRunnableThread *KinectThread;
	
	/** Used to stop the thread execution. */
	FThreadSafeCounter StopThreadCounter;

	/** The device that starts this thread. */
	AzureKinectDevice *KinectDevice;
};
