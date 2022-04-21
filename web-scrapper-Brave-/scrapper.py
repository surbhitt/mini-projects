
#!/usr/bin/env python -tt 	
import io
from selenium import webdriver
from selenium.webdriver.common.by import By
import time
import requests
from PIL import Image

def get_images_from_google(wd, delay, max_images):
	def scroll_down(wd):
		wd.execute_script("window.scrollTo(0, document.body.scrollHeight);")
		time.sleep(delay)

# the url of the google image page from where you want to download pics 
# eg: https://www.google.com/search?q=cat&source=lnms&tbm=isch&sa=X&ved=2ahUKEwiTkdmk6f7zAhVWU30KHRdiAe0Q_AUoAXoECAEQAw&biw=1536&bih=758&dpr=1.25
	url = " here "
	
	wd.get(url)

	image_urls = set()
	skips = 0

	while len(image_urls) + skips < max_images:
		scroll_down(wd)

		thumbnails = wd.find_elements(By.CLASS_NAME, "Q4LuWd")

		for img in thumbnails[len(image_urls) + skips:max_images]:
			try: 
				img.click()
				time.sleep(delay)
			except:
				continue

			images = wd.find_elements(By.CLASS_NAME, "n3VNCb")
			for image in images:
				if image.get_attribute('src') in image_urls:
				 	max_images	+= 1
				 	skips += 1			
				 	break
				if image.get_attribute('src') and 'http' in image.get_attribute('src'):
					image_urls.add(image.get_attribute('src'))
					print('found image')

	return image_urls


def download_img(download_path, url, file_name):
	try:
		image_content = requests.get(url).content
		image_file = io.BytesIO(image_content)
		image = Image.open(image_file)
		file_path = download_path + file_name

		with open(file_path, "wb") as f:
			image.save(f, "JPEG")
		print("SUCCESS")

	except Exception as e:
		print('FAILED-',e)


def main():

# path of where you have your chromedriver 
	PATH=" here "
# path to you brave executable application
	brave_path = " here "

	option = webdriver.ChromeOptions()
	option.binary_location = brave_path

	wd = webdriver.Chrome(executable_path=PATH, chrome_options=option)

# get_images_from_google(wd, number-of-seconds-delayed-for-loading, number-of-pics-to-download)
	urls = get_images_from_google(wd, 1, 1)

	for i, url in enumerate(urls):
		download_img("images/", url, str(i) + ".jpg")
	wd.quit()


if __name__=="__main__":
	main()
