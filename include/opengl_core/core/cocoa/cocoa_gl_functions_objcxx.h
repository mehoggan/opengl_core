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
#import "opengl_core/core/gl_functions.h"

#import <Foundation/Foundation.h>

@interface gl_functions_objcxx : NSObject
{
}

+(void) load_1_2:(void *) sym_loader;
+(void) load_1_3:(void *) sym_loader;
+(void) load_1_4:(void *) sym_loader;
+(void) load_1_5:(void *) sym_loader;
+(void) load_2_0:(void *) sym_loader;
+(void) load_2_1:(void *) sym_loader;
+(void) load_3_0:(void *) sym_loader;

+(void) configure:(void *)context;

@end

