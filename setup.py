from distutils.core import setup, Extension

def main():
	setup(name="PYModule",
		version="1.0.0",
		description="TEST Module",
		author="<your name>",
		author_email="your_email@gmail.com",
		ext_modules=[Extension("PYModule", ["module.c", "class_py.c", "class.c"])])

if __name__ == "__main__":
	main()
