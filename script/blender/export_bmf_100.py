# The MIT License (MIT)
# 
# Copyright (c) 2013 Paul Holden et al. (See AUTHORS)
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.

bl_info = {
    "name":         "Bakge Mesh File v1.0.0",
    "author":       "Paul Holden",
    "blender":      (2,6,2),
    "version":      (1,0,0),
    "location":     "File > Import-Export",
    "description":  "Export Bakge Mesh File v1.0.0 specification.",
    "category":     "Import-Export"
}
        
import bpy
from bpy_extras.io_utils import ExportHelper

class ExportFormat(bpy.types.Operator, ExportHelper):
    filename_ext = ".bmf";
    bl_idname = "filename.bmf";
    bl_label = "Export BMF v1.0.0";
    bl_options = {
        'PRESET'
    };
    
    def execute(self, context):
        return {
            'Finished'
        };

def menu_func(self, context):
    self.layout.operator(ExportFormat.bl_idname,
            text="Bakge Mesh File v1.0.0 (.bmf)");

def register():
    bpy.utils.register_module(__name__);
    bpy.types.INFO_MT_file_export.append(menu_func);
    
def unregister():
    bpy.utils.unregister_module(__name__);
    bpy.types.INFO_MT_file_export.remove(menu_func);

if __name__ == "__main__":
    register()