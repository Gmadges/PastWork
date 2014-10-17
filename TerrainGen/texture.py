import Image
import os

data = [line.strip() for line in open('/usr/tmp/TextData.txt')]

DATA_SIZE = int(data[0])

count = 1
size = (512,512)
img = Image.new( 'RGB', (DATA_SIZE,DATA_SIZE), "black") # create a new black image 
pixels = img.load() # create the pixel map 
 
  
for i in range(DATA_SIZE):    # for every pixel: 
	for j in range(DATA_SIZE): 
		value = float(data[count]) 
		value = (value + 5)*25.5
		if(value > 255): value = 255
		if(value < 0):       value = 0
		pixels[i,j] = (int(0), int(value/2), int(value)) # set the colour accordingly 
		count+=1
img.rotate(0)
img = img.resize(size, Image.ANTIALIAS)
img = img.transpose(Image.FLIP_LEFT_RIGHT)

img.save("/usr/tmp/texture.jpg")

#Cleanup
#os.system("mv /usr/tmp/texture.jpg ~/maya/2014-x64/scripts") 
#os.remove('/usr/tmp/TextData.txt')


