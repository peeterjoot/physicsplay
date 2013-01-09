sudo apt-get remove texlive*
sudo apt-get autoremove
sudo apt-get clean
sudo apt-get update
sudo apt-get autoclean
sudo apt-get check

sudo rm /var/lib/dpkg/info/texlive*.postrm
sudo rm /var/lib/dpkg/info/texlive*.list

sudo dpkg --purge --force-all texlive*
sudo dpkg --purge --force-all tex-common*

#sudo apt-get install texlive-latex-base
#sudo apt-get install texlive-latex-extra
#sudo apt-get install texlive-full
