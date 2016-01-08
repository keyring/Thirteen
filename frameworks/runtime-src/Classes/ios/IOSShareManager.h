//
//  IOSShareManager.h
//  Thirteen
//
//  Created by keyring on 1/6/16.
//
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface IOSShareManager : NSObject

+ (IOSShareManager *) getInstance;
- (void)share:(CGPoint)pos;
- (void)goToAppStore;

@property (nonatomic, readwrite, retain) id viewController;

@end