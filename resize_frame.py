
import os

file_path = 'c:/Users/Nebouli/Documents/employe/mainwindow.ui'

with open(file_path, 'r', encoding='utf-8') as f:
    lines = f.readlines()

new_lines = []
inside_frame_10 = False
inside_geometry = False
inside_rect = False

for line in lines:
    if '<widget class="QFrame" name="frame_10">' in line:
        inside_frame_10 = True
    
    if inside_frame_10 and '<property name="geometry">' in line:
        inside_geometry = True
    
    if inside_frame_10 and inside_geometry and '<rect>' in line:
        inside_rect = True
        
    if inside_frame_10 and inside_geometry and inside_rect:
        if '<width>921</width>' in line:
            line = line.replace('921', '1200')
        elif '<height>691</height>' in line:
            line = line.replace('691', '750')
            # Reset flags after modification to avoid affecting other widgets if nested (though unlikely for geometry)
            inside_frame_10 = False 
            inside_geometry = False
            inside_rect = False
            
    new_lines.append(line)

with open(file_path, 'w', encoding='utf-8') as f:
    f.writelines(new_lines)

print("File updated successfully.")
