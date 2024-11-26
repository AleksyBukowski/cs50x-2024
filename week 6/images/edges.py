from PIL import Image, ImageFilter

before = Image.open("cat.jpg")
after = before.filter(ImageFilter.FIND_EDGES)
after.save("cat_edges.jpg")
