import maya.cmds as cmds
import random
import os
import sys

# create the array bigger than it needs to be with default values set to zero


def createTerrainData(DATA_SIZE, SEED, h, jag):
	
	global dataArray
	
	dataArray = [[SEED]*DATA_SIZE for x in range(0, DATA_SIZE)]
	
	for i in range(0, DATA_SIZE):
		for j in range(0, DATA_SIZE):
			dataArray[i][j] = SEED
			
	
			
	sideLength = DATA_SIZE-1

	while(sideLength >= 2):
		halfside = sideLength/2
		
		#Square pass
		for x in range(0, (DATA_SIZE-1), sideLength):
			for y in range(0, (DATA_SIZE-1), sideLength):		
				avg = ((dataArray[x][y] 						+ 	#top left
						dataArray[x+sideLength][y]   			+	#top right
						dataArray[x][y+sideLength]   			+ 	#lower left
						dataArray[x+sideLength][y+sideLength]) 	/	#lower right
						4)
					
				offset = random.uniform(-h,h)
				
				height = avg + offset
				
				dataArray[x+halfside][y+halfside] = height
		
		# Diamond pass
		for x in range(0,(DATA_SIZE),halfside):
			for y in range(((x+halfside)%sideLength), DATA_SIZE, sideLength):		
				avg = ((dataArray[(x-halfside+DATA_SIZE)%DATA_SIZE][y] 		+ #left
						dataArray[(x+halfside)%DATA_SIZE][y]					+ #right
						dataArray[x][(y+halfside)%DATA_SIZE]					+ #below
						dataArray[x][(y-halfside+DATA_SIZE)%DATA_SIZE])			/ #above
						4)											  			#divide by 4
				
				offset = random.uniform(-h,h) 
				
				height = avg + offset
		
				dataArray[x][y] = height
				
				y += sideLength
			
		sideLength = halfside
		h = h*jag

	return dataArray
	
def GenTerrain(DATA_SIZE, SEED, h, j):
	
	createTerrainData(DATA_SIZE, SEED, h, j)
	
	name = 'Terrain'
	totalPoints=(DATA_SIZE)*(DATA_SIZE)
	
	if (cmds.objExists(name) == True):
		cmds.delete(name)
    
	cmds.polyPlane( n=name, sx=(DATA_SIZE-1), sy=(DATA_SIZE-1), h=20, w=20)
	count = 0
	
	cmds.progressWindow(title='Setting Points', progress=count, max = totalPoints, status='Setting: 0/'+str(totalPoints))            
                         
	for i in xrange(DATA_SIZE):
		if True: cmds.refresh()
		cmds.delete(name, ch = True)
		for j in xrange(DATA_SIZE):
					offset = dataArray[i][j]
					cmds.polyMoveVertex( name+'.vtx['+str(count)+']', ws = True, ty = offset, cch=True)
					cmds.progressWindow(edit=True, progress=count, status='Setting: '+str(count))
					count+=1
                                    
	cmds.progressWindow(endProgress=1)

	#cmds.polySmooth(n=name, cch = True)
	cmds.delete(name, ch = True)

	

def createCustomtexture(DATA_SIZE):
	file = open("/usr/tmp/TextData.txt", "w") 
	file.write(str(DATA_SIZE)+"\n")
                     
	for i in xrange(DATA_SIZE):
		for j in xrange(DATA_SIZE):
					offset = dataArray[i][j]
					file.write(str(offset)+"\n")
	
	file.close()

	


	
def ImportCustomTexture(name):
	
	os.system("cd ~/maya/2014-x64/scripts; python texture.py")
	
	file = '/usr/tmp/texture.jpg'
	
	#create a shader
	shader=cmds.shadingNode( "blinn", asShader=True )

	#a file texture node
	shaderName = file_node=cmds.shadingNode( "file", asTexture=True )
	
	print shaderName
	
	#attach file to node
	cmds.setAttr( '%s.fileTextureName' %file_node, file, type = "string")
 
	# a shading group
	shading_group= cmds.sets(renderable=True,noSurfaceShader=True,empty=True)

	#connect shader to sg surface shader
	cmds.connectAttr('%s.outColor' %shader ,'%s.surfaceShader' %shading_group)

	#connect file texture node to shader's color
	cmds.connectAttr('%s.outColor' %file_node, '%s.color' %shader)

	cmds.sets(name, edit=True, forceElement=shading_group)
	
	#cleanup
	#os.system("cp /usr/tmp/texture.jpg ~/maya/2014-x64/scripts")
	

	               
	             
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
