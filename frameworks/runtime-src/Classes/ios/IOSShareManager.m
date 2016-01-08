//
//  IOSShareManager.m
//  Thirteen
//
//  Created by keyring on 1/6/16.
//
//

#import "IOSShareManager.h"

@interface IOSShareManager()
@property (strong, nonatomic) UIPopoverController *activityPopover;
@end

@implementation IOSShareManager

+ (IOSShareManager *) getInstance
{
    static IOSShareManager* gameMgr = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        gameMgr = [[self alloc] init];
    });
    return gameMgr;
}

- (void)share:(CGPoint)pos
{
    // 你可以先截屏保存到document下，这里的image读取document下面。
    NSString *aPath3=[NSString stringWithFormat:@"%@/Documents/CaptureScreen.png", NSHomeDirectory()];
    UIImage *image=[[UIImage alloc]initWithContentsOfFile:aPath3];
    NSString *msg = @"You can add some description info here!";
    
    UIActivityViewController *activityViewController = [[UIActivityViewController alloc] initWithActivityItems:@[image, msg] applicationActivities:nil];
    
//    NSArray *excludedActivities = @[UIActivityTypePostToTwitter, UIActivityTypePostToFacebook,
//UIActivityTypePostToWeibo,
//UIActivityTypeMessage, UIActivityTypeMail,
//UIActivityTypePrint, UIActivityTypeCopyToPasteboard,
//UIActivityTypeAssignToContact, UIActivityTypeSaveToCameraRoll,
//UIActivityTypeAddToReadingList, UIActivityTypePostToFlickr,
//UIActivityTypePostToVimeo, UIActivityTypePostToTencentWeibo];
//    activityViewController.excludedActivityTypes = excludedActivities;
//    
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
        //iPhone 从底部向上滑出view
        [self.viewController presentViewController:activityViewController animated:YES completion:nil];
    } else {
        //iPad, 弹出view
        if (![self.activityPopover isPopoverVisible]) {
            self.activityPopover = [[UIPopoverController alloc] initWithContentViewController:activityViewController];
            [self.activityPopover presentPopoverFromRect:CGRectMake(pos.x, pos.y, 0, 0) inView:((UIViewController *)self.viewController).view permittedArrowDirections:UIPopoverArrowDirectionAny animated:YES];
        } else {
            //Dismiss view，当重复点击时
            [self.activityPopover dismissPopoverAnimated:YES];
        }
    }
}

- (id)init
{
    self = [super init];
    if (self) {
        // init code here
        
    }
    return self;
}

- (void) dealloc
{
    [super dealloc];
}

-(void)goToAppStore
{
    NSString *str = [NSString stringWithFormat:
                     @"itms-apps://itunes.apple.com/app/id%d",1072124511];
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:str]];
    
}

@end