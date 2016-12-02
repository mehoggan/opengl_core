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
#import "opengl_core/core/render_context.h"

#import <Foundation/Foundation.h>

@interface render_context_objcxx : NSObject
{
}

-(void) init_render_context:(void *)system :(void *)window
    :(void *)fbc;
-(void) make_current:(void *)window;
-(void) make_not_current;
-(void) destroy;

-(int) query_major_version;
-(int) query_minor_version;

@end