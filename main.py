from PIL import Image
import numpy as np
import matplotlib.pyplot as plt
import mymodule

im = np.array(Image.open('kamo.jpg'))

im = mymodule.sepia(im)

print(type(im))
print(im.dtype)
print(im.shape)

plt.imshow(im)
plt.show()
