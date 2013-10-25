#ifndef  APP_DELEGATE_H
#define  APP_DELEGATE_H

#include "cocos2d.h"

typedef struct tagResource
{
    cocos2d::Size size;
    char directory[100];
} Resource;

static Resource resPhone        =  { cocos2d::Size(480, 320),   "iphone" };
static Resource resPhoneRetina  =  { cocos2d::Size(960, 640),   "iphonehd" };
static Resource resTablet       =  { cocos2d::Size(1024, 768),  "ipad"   };
static Resource resTabletRetina =  { cocos2d::Size(2048, 1536), "ipadhd" };
static cocos2d::Size designResolutionSize = cocos2d::Size(1024, 768);

/**
@brief    The cocos2d Application.

The reason for implement as private inheritance is to hide some interface call by Director.
*/
class  AppDelegate : private cocos2d::Application
{
public:
    AppDelegate();
    virtual ~AppDelegate();

    /**
    @brief    Implement Director and Scene init code here.
    @return true    Initialize success, app continue.
    @return false   Initialize failed, app terminate.
    */
    virtual bool applicationDidFinishLaunching();

    /**
    @brief  The function be called when the application enter background
    @param  the pointer of the application
    */
    virtual void applicationDidEnterBackground();

    /**
    @brief  The function be called when the application enter foreground
    @param  the pointer of the application
    */
    virtual void applicationWillEnterForeground();
};

#endif // _APP_DELEGATE_H_

