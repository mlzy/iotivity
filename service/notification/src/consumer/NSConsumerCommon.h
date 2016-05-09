//******************************************************************
//
// Copyright 2016 Samsung Electronics All Rights Reserved.
//
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

#ifndef _NS_CONSUMER_CONSTANTS_H_
#define _NS_CONSUMER_CONSTANTS_H_

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <stdio.h>
#include <stdbool.h>

#include "NSCommon.h"
#include "NSStructs.h"
#include "ocstack.h"

#define NS_LOG_PRINTF 0

#define __NS_FILE__ ( strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__ )

const char * NS_CONVERT_LEVEL(int level);

// TODO fix ns log using oic log.
#ifdef TB_LOG
#include "logger.h"
#define NS_CONSUMER_LOG_V(level, format, ...) (OIC_LOG_V((level), __NS_FILE__, (format), __VA_ARGS__))
#define NS_CONSUMER_LOG(level, msg) (OIC_LOG((level), __NS_FILE__, (msg)))
#else
#include "logger.h"
#define NS_CONSUMER_LOG_V(level, format, ...) { \
        printf("%s: %s ", NS_CONVERT_LEVEL(level), __NS_FILE__); \
        printf((format), __VA_ARGS__); \
        printf("\n"); }
#define NS_CONSUMER_LOG(level, msg) { \
        printf("%s: %s ", NS_CONVERT_LEVEL(level), __NS_FILE__); \
        printf((msg)); \
        printf("\n"); }

#endif

#define NS_QOS OC_LOW_QOS
#define NS_RESOURCE_TYPE "oic.r.notification"
#define NS_RESOURCE_URI "/notification"
#define NS_INTERFACE_BASELINE "oic.if.baseline"
#define NS_INTERFACE_NOTIFICATION "oic.if.notification"
#define NS_RESOURCE_QUERY "/oic/res"

#define NS_DISCOVER_QUERY "/oic/res?rt=oic.r.notification"

typedef OCStackApplicationResult (*onRIResponseListener)(
        void *, OCDoHandle, OCClientResponse *);

typedef enum
{
    Read,
    Dismiss,
    Notification,
} NSConsumerMessageTypes;

typedef struct
{
    // Mandatory
    char * mId;
    char * mTitle;

    //Optional
    char * mContentText;

    OCDevAddr * addr;
    char * syncUri;
    NSConsumerMessageTypes type;
} NSMessage_consumer;

bool NSIsStartedConsumer();
void NSSetIsStartedConsumer(bool setValue);

void NSSetDiscoverProviderCb(NSProviderDiscoveredCallback cb);
void NSDiscoveredProvider(NSProvider * handle);

void NSSetNotificationPostedCb(NSNotificationReceivedCallback  cb);
void NSNotificationPost(NSProvider * provider, NSMessage * obj);

void NSSetNotificationSyncCb(NSSyncCallback cb);
void NSNotificationSync(NSProvider * provider, NSSync * sync);

onRIResponseListener NSGetResponseListener();
void NSSetResponseListener(onRIResponseListener cb);

NSTask * NSMakeTask(NSTaskType, void *);

NSResult NSConsumerPushEvent(NSTask *);

NSMessage_consumer * NSCopyMessage(NSMessage_consumer *);
void NSRemoveMessage(NSMessage_consumer *);

OCStackResult NSRequestToResourceIntrospection(OCDoHandle * handle,
        OCMethod method, const OCDevAddr * addr,
        const char * queryUrl, OCPayload * payload, void * callback);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _NS_CONSUMER_CONSTANTS_H_