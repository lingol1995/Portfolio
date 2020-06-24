#1301186 - AG0932A – Technical Art Applications
# please place all files in the "Images" folder in your
# Documents\maya\<maya version>\prefs\icons folder 

### This script should be useful for both the animator and the programmer. The tool is arranged in tabs: one for rigging; one for animation; and one for the picker. 
#Under the rigging tab, it allows the user to create control shapes (either circle or square), group and rename them. This will automatically add the appropriate prefixes and suffixes to the shapes and groups. Under this tab the user can also create a new joint in their specified position. 
#Under the animation tab, the user can use the sliders to curl the fingers on the model. Also, by clicking on the images at the bottom, the user can position the model into the position depicted in the images.
#Under the picker tab, the user can select the buttons and the corresponding control shapes will be selected in the viewport. 
##########################################################

#Move all fingers on Right Hand
def MoveFinger(*args):
	cmds.setAttr("ctrl_R_Wrist.All_Curl",*args)
#Moves index finger on right wrist
def MoveIndex(*args):
	cmds.setAttr("ctrl_R_Wrist.Index_Curl",*args)
#Moves middle right finger
def MoveMiddle(* args):
	cmds.setAttr("ctrl_R_Wrist.Mid_Curl",*args)
#Moves Ring finger
def MoveRing(* args):
	cmds.setAttr("ctrl_R_Wrist.Ring_Curl",*args)
#Moves Pinky finger
def MovePinky(* args):
	cmds.setAttr("ctrl_R_Wrist.Pinky_Curl",*args)
#Moves all Left Fingers
def MoveLeftFinger(*args):
	cmds.setAttr("ctrl_L_Wrist.Thumb",*args)
#Moves Left Index finger
def MoveLeftIndex(*args):
	cmds.setAttr("ctrl_L_Wrist.Index_Curl",*args)
#Moves Left middle finger
def MoveLeftMiddle(* args):
	cmds.setAttr("ctrl_L_Wrist.MiddleCurl",*args)
#Moves left ring finger
def MoveLeftRing(* args):
	cmds.setAttr("ctrl_L_Wrist.RingCurl",*args)
#Moves left pinky
def MoveLeftPinky(* args):
	cmds.setAttr("ctrl_L_Wrist.PinkyCurl",*args)

#Makes circle and allows user to rename it (promptdialog)
def MakeCircle(): 
    result = cmds.promptDialog(title='Rename Object',message='Enter Name:',button=['OK', 'Cancel'],defaultButton='OK',cancelButton='Cancel',dismissString='Cancel')
    if result == 'OK':
        texty = cmds.promptDialog(query=True, text=True)		#Get typed name
        cmds.circle(n=texty)	#call circle the name
        cmds.group(texty, n='grp_'+texty)

#Make square the same way as circle
def MakeSquare(): 
    result = cmds.promptDialog(title='Rename Object',message='Enter Name:',button=['OK', 'Cancel'],defaultButton='OK',cancelButton='Cancel',dismissString='Cancel')
    if result == 'OK':
        texty = cmds.promptDialog(query=True, text=True)
        cmds.nurbsSquare(n=texty)
        cmds.group(texty, n='grp_'+texty)

#Place a joint at specified position and named by user.
def placejoint():
    result2 = cmds.promptDialog(title='Rename Object',message='Enter Name:',button=['OK', 'Cancel'],defaultButton='OK',cancelButton='Cancel',dismissString='Cancel')
    if result2 == 'OK':
        jointname = cmds.promptDialog(query=True, text=True)	#get name
        jointX = cmds.floatFieldGrp(jointfields, query = True, value1 = True)	#position x
        jointY = cmds.floatFieldGrp(jointfields, query=True, value2 = True)	#position y
        jointZ = cmds.floatFieldGrp(jointfields, query=True, value2 = True)	#position z
        jointmade = cmds.joint(name='jnt_'+ jointname ,p=(jointX, jointY, jointZ))

#Bend Right Leg
def Bendleg():
	cmds.setAttr("ctrl_R_ankle.legbend ",20)
#Bend Left Leg
def Bendleftleg():
	cmds.setAttr("ctrl_L_Ankle.Bendleg",20)

#Swing one arm forward, the other back
def ArmBend():
    cmds.setAttr("ctrl_L_Wrist.ArmSwing",20)
    cmds.setAttr("ctrl_R_Wrist.ArmSwing",-20)
#Swing one arm back the other forward
def ArmBend2():
    cmds.setAttr("ctrl_L_Wrist.ArmSwing",-20)
    cmds.setAttr("ctrl_R_Wrist.ArmSwing", 20)
#########################################################################	
#Create window with form layout and tabs
newest = cmds.window(title ="Riku Rigging Tool", widthHeight=(500, 400) )
form = cmds.formLayout()
tabs = cmds.tabLayout(innerMarginWidth=6, innerMarginHeight=9)
cmds.formLayout( form, edit=True, attachForm=((tabs, 'top', 0), (tabs, 'left', 0), (tabs, 'bottom', 0), (tabs, 'right', 0)) )	#set out tabs

#####################################################################
#First tab (Rigging Tab)
#Buttons – Square, Cube, Torus, Circle, Joint Placer
#Other – Joint fields, Check Box, Separators
#Layout - RowColumn (2 Columns)
child1 = maya.cmds.rowColumnLayout(numberOfColumns=2, columnWidth=[(1, 300), (2, 100)],cs = [(1,20),(2,0)], rs = [(1,20),(2,20)])
cmds.symbolButton(image='square.png', command="MakeSquare()")
maya.cmds.symbolButton(image='cube.png',  command="maya.cmds.polyCube()")
cmds.symbolButton( image='circle.png' ,command = "MakeCircle()")
cmds.symbolButton(image='torus.png', command="cmds.polyTorus()")
cmds. symbolButton(image='torus.png', command="cmds.joint()")		#this places a joint, however the picture is a torus since I was unable to find an appropriate image
cmds.symbolButton(image='cylinder.png', command="cmds.polyCylinder()")
cmds.separator( height=40, style='in' )
cmds.separator( height=40, style='in' )
jointfields = cmds.floatFieldGrp(numberOfFields = 3)		#3 fields
#ctrlshape = cmds.checkBox(label = 'control shape attached')	#check box
#attach_shape = cmds.checkBox(ctrlshape, query = True, value = True)

cmds.button(label='place joint', command="placejoint()")
cmds.setParent( '..' )

#############################################################################
#Second Tab (Animation Tab)
#Buttons – Bend Leg symbols
#Other – Sliders for all fingers, Separators, Text
#Layout – Form layout

child2 = cmds.formLayout()
sep = cmds.separator(style='out')
sep2 = cmds.separator(style='out' )
righttext = cmds.text(label = "Right Hand", align = 'left')
####################FINGER SLIDERS#####################################
fingers = cmds.floatSliderGrp(label = 'All Right fingers',field=True, min=0, max=20, value=0, dc=MoveFinger)	#all right fingers
fingers2 = cmds.floatSliderGrp(label = 'Right Index',field=True, min=0, max=20, value=0, dc=MoveIndex)		#right index
fingers3 = cmds.floatSliderGrp(label = 'Right Middle',field=True, min=0, max=20, value=0, dc=MoveMiddle)	#right middle
fingers4 = cmds.floatSliderGrp(label = 'Right Ring',field=True, min=0, max=20, value=0, dc=MoveRing)		#right ring
fingers5 = cmds.floatSliderGrp(label = 'Right Pinky',field=True, min=0, max=20, value=0, dc=MovePinky)		#right pinky
sep3 = cmds.separator( height=60, style='in' )
lefttext = cmds.text(label = "Left Hand", align = 'left')
fingers6 = cmds.floatSliderGrp(label = 'Left Thumb',field=True, min=0, max=20, value=0, dc=MoveLeftFinger)	#Left Thumb
fingers7 = cmds.floatSliderGrp(label = 'Left Index',field=True, min=0, max=20, value=0, dc=MoveLeftIndex)	#Left index
fingers8 = cmds.floatSliderGrp(label = 'Left Middle',field=True, min=0, max=20, value=0, dc=MoveLeftMiddle)	#Left Middle
fingers9 = cmds.floatSliderGrp(label = 'Left Ring',field=True, min=0, max=20, value=0, dc=MoveLeftRing)	#Left Ring
fingers10 = cmds.floatSliderGrp(label = 'Left Pinky',field=True, min=0, max=20, value=0, dc=MoveLeftPinky)	#Left pinky
cmds.separator( height=60, style='in' )
bendleg = cmds.symbolButton( width = 100, height=100, image='bendleg.jpg', command="Bendleg()" )		#image button bend leg
bendleftleg = cmds.symbolButton( width = 100, height=100, image='bendleftleg.jpg', command="Bendleftleg()" )	#image button bend leg
swingarms = cmds.symbolButton( width = 100, height=100, image='bendarm.jpg', command="ArmBend()" )				#image button swing arms
swingarms2 = cmds.symbolButton( width = 100, height=100, image='bendarmright.jpg', command="ArmBend2()" )	#image button swing arms opposite way

cmds.setParent( '..' )

###################POSITIONING OF SLIDERS, TEXT AND BUTTONS####################
maya.cmds.formLayout(child2, edit=True, attachForm=[[sep, "top", 0], [sep, "left", 0]])			#separator
maya.cmds.formLayout(child2, edit=True, attachForm=[[sep2, "top", 10]])							#separator
maya.cmds.formLayout(child2, edit=True, attachForm=[[righttext, "top", 20], [righttext, "left", 0]])	#text (Right hand section)
maya.cmds.formLayout(child2, edit=True, attachForm=[[fingers, "top", 30], [fingers, "left", 20]])	#all right fingers
maya.cmds.formLayout(child2, edit=True, attachForm=[[fingers2, "top", 50], [fingers2, "left", 20]])	#right index finger
maya.cmds.formLayout(child2, edit=True, attachForm=[[fingers3, "top", 70], [fingers3, "left", 20]])	#right middle
maya.cmds.formLayout(child2, edit=True, attachForm=[[fingers4, "top", 90], [fingers4, "left", 20]])		#right pinky
maya.cmds.formLayout(child2, edit=True, attachForm=[[ fingers5, "top", 110], [fingers5, "left", 20]])	#right thumb
maya.cmds.formLayout(child2, edit=True, attachForm=[[lefttext, "top", 130], [righttext, "left", 0]])	#text (Left hand section)
maya.cmds.formLayout(child2, edit=True, attachForm=[[sep3, "top", 130], [sep3, "left", 0]])				#separator
maya.cmds.formLayout(child2, edit=True, attachForm=[[fingers6, "top", 140], [fingers6, "left", 20]])	#Left thumb
maya.cmds.formLayout(child2, edit=True, attachForm=[[fingers7, "top", 160], [fingers7, "left", 20]])	#Left index
maya.cmds.formLayout(child2, edit=True, attachForm=[[fingers8, "top", 180], [fingers8, "left", 20]])	#Left Middle
maya.cmds.formLayout(child2, edit=True, attachForm=[[ fingers9, "top", 200], [fingers9, "left", 20]])	#Left Ring
maya.cmds.formLayout(child2, edit=True, attachForm=[[ fingers10, "top", 220], [fingers10, "left", 20]])	#Left Pinky
maya.cmds.formLayout(child2, edit=True, attachForm=[[ bendleg, "top", 250], [bendleg, "left", 20]])		#Image button bend leg
maya.cmds.formLayout(child2, edit=True, attachForm=[[ bendleftleg, "top", 250], [bendleftleg, "left", 120]])	#Image button left leg bend
maya.cmds.formLayout(child2, edit=True, attachForm=[[ swingarms, "top", 250], [swingarms, "left", 230]])		#image button swing arms
maya.cmds.formLayout(child2, edit=True, attachForm=[[ swingarms2, "top", 250], [swingarms2, "left",  330]])		#Image button swing arms in opposite direction

#########################################################################
#Third Tab - Picker Tab
#Buttons - Right Wrist, Left Wrist, Right leg, Left leg
#Layout - Form Layout

child3 = maya.cmds.formLayout()
image_name = maya.cmds.image(width = 400, height = 400, image="body.jpg")		#Riku image
r_wrist_button = maya.cmds.button(backgroundColor = [1.0,0.0,0.0],label="Right wrist", command="cmds.select('ctrl_R_Wrist')")	#wrist button, red in colour
l_wrist_button = maya.cmds.button(backgroundColor = [1.0,0.0,0.0], label="Left wrist", command= "cmds.select('ctrl_L_Wrist')")
l_leg_button = maya.cmds.button(backgroundColor = [0.0,0.0,1.0], label="Left leg", command = "cmds.select('ctrl_L_Ankle')")		#Leg button, blue in colour
r_leg_button = maya.cmds.button(backgroundColor = [0.0,0.0,1.0], label="Right leg", command = "cmds.select('ctrl_R_ankle')") 
cmds.setParent( '..' )
#####################TAB 3 LAYOUT############################################
maya.cmds.formLayout(child3, edit=True, attachForm=[[image_name, "top", 0], [image_name, "left", 0]])	#Riku image
maya.cmds.formLayout(child3, edit=True, attachForm=[[r_wrist_button, "top", 70], [r_wrist_button, "left", 20]])		#wrist buttons layout, Positioned at Riku image wrists
maya.cmds.formLayout(child3, edit=True, attachForm=[[l_wrist_button, "top", 70], [l_wrist_button, "left", 300]])	#wrist buttons layout, Positioned at Riku image wrists
maya.cmds.formLayout(child3, edit=True, attachForm=[[r_leg_button, "top", 300], [r_leg_button, "left", 100]])		#Leg buttons layout, Positined at Riku image legs
maya.cmds.formLayout(child3, edit=True, attachForm=[[l_leg_button, "top", 300], [l_leg_button, "left", 250]])		#Leg buttons layout, Positioned at Riku image legs

#all tabs, named.
cmds.tabLayout(tabs, edit=True, tabLabel=((child1, 'Rigging'), (child2, 'Animating') , (child3, 'Picker')))

cmds.showWindow(newest)

