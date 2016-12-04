/* Copyright (C)
 *
 * Copyright 2013 Matthew Everett Hoggan
 *
 * Licensed under the Apache License, Version 2.0 (the "License")
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writting, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#import "opengl_core/core/render_system.h"
#import "opengl_core/core/cocoa/cocoa_render_window_objcxx.h"

#import <AppKit/AppKit.h>
#import <Cocoa/Cocoa.h>
#import <Foundation/Foundation.h>

@interface render_system_objcxx : NSObject
{
  NSAutoreleasePool *pool;
  NSWindowController *window_controller;
  render_window_objcxx *render_window;
}

-(void) render_loop;
-(bool) init_system;
-(void) terminate_system;
-(void) destroy;

@end
