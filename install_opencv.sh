
#!/usr/bin/env bash

# Alternative Installation script for Opencv3 on Ubuntu 16.04 only.
# Reference:  1) https://www.youtube.com/watch?v=4nQtx2ANLL0


#Step1: Install OpenCV3 dependencies on Ubuntu 16.04
echo "[Updating and upgrading before Installation] \n \n"
sudo apt-get update
sudo apt-get upgrade
echo "\n \n"
echo "[Installing essentials....this might take some time] \n \n".
sudo apt-get install python3-pip

pip3 install opencv-python
