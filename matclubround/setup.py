from distutils.core import setup, Extension


def main():
  setup(
    name="matclubround",
    version="1.0.0",
    description="matclubround module in python",
    author="Mike",
    author_email="mikehuls42@gmail.com",
    ext_modules=[Extension("matclubround", ["matclubround.c"])]
  )

if (__name__ == "__main__"):
  main()