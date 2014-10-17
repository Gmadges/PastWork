import maya.cmds as cmds
import TerrainLib as ter 

reload(ter)



DATA_SIZE = 33
SEED = 0.0
h = None
jag = None


cWindow = cmds.window(title="Terrain Generator", wh=(400,500), sizeable=False)
tabs = cmds.tabLayout(innerMarginWidth=5,innerMarginHeight=5)


TerrainGen = cmds.columnLayout(adj=True)
cmds.text(label="  Set Parameters for the terrain and click Generate. ")
cmds.text(label="  -------------------------------------------------- ")

cmds.text(label=" jaggedness? ")
slider1 = cmds.floatSliderGrp(field=True,minValue=0.01,maxValue=1.00,value=0.5)
jag = cmds.floatSliderGrp(slider1,q=True,v=True)

cmds.text(label=" height ")
slider2 = cmds.floatSliderGrp(field=True,minValue=1.0,maxValue=10.0,value=5.0)
h = cmds.floatSliderGrp(slider2,q=True,v=True)


cmds.button(label=" Generate ", command='ter.GenTerrain(DATA_SIZE, SEED, h, jag)')
cmds.setParent('..')

TextureGen = cmds.columnLayout(adj=True)
cmds.text(label="  This is a test GUI ")
cmds.text(label="  ------------------------------------------- ")

cmds.button(label=" GUItoGUI  ", command="GUItoGUI()")
cmds.setParent('..')


v_a = None
v_b = None
v_c = None
Example3 = cmds.columnLayout(adj=True)
cmds.text(label="Sliders Generation")
cmds.text(label=" Value A")
v_a = cmds.floatSliderGrp(field=True,minValue=0.0,maxValue=5.0,value=1.0)
cmds.text(label=" Value B")
v_b = cmds.floatSliderGrp(field=True,minValue=0.0,maxValue=5.0,value=1.0)
cmds.button(label= "  GENERATE  ", command='Sliders()')
cmds.separator(h=4, style="in")
cmds.text(label="")
cmds.text(label=" Value C Run-Time")
v_c = cmds.floatSliderGrp(field=True,minValue=0.0,maxValue=5.0,value=1.0, dragCommand='SlidersRT(cmds.floatSliderGrp(v_c,q=1,v=1))')
cmds.setParent('..')


HelpCard = cmds.columnLayout(adj=True)
cmds.setParent('..')
cmds.setParent('..')


cmds.tabLayout(tabs,edit=True,tabLabel=((TerrainGen,"Terrain Gen"),(TextureGen,"Texture Gen"),(Example3,"Example3"),(HelpCard,"Help Card")))

cmds.showWindow(cWindow)

#ter.createCustomtexture(DATA_SIZE, dataArray)

#ter.ImportCustomTexture(name)




 








