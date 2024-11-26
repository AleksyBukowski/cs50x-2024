from PIL import Image, ImageFilter

before = Image.open("cat.jpg")
after = before.filter(ImageFilter.BoxBlur(10))
after.save(("cat_blur.jpg"))
