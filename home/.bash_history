vim
cd project/p2284/
make P2284.pdf
pandoc --version
exit
curl --help
mkdir ~/pandoc_latest
curl -o ~/pandoc_latest/pandoc.deb CMD ["cd", "projects/p2284"]
PANDOC_VERSION=2.15; curl -o ~/pandoc_latest/pandoc.deb https://github.com/jgm/pandoc/releases/download/${PANDOC_VERSION}/pandoc-${PANDOC_VERSION}-1-amd64.deb
apt-get install ~/pandoc_latest/pandoc.deb 
dpkg -i ~/pandoc_latest/pandoc.deb 
mv ~/pandoc_latest/pandoc.deb ~/pandoc_latest/
ll ~/pandoc_latest/
dpkg -i ~/pandoc_latest/pandoc-2.15-1-amd64.deb 
PANDOC_VERSION=2.15; curl -o ~/pandoc_latest/pandoc.deb https://github.com/jgm/pandoc/releases/download/${PANDOC_VERSION}/pandoc-{PANDOC_VERSION}-linux-amd64.tar.gz
mv ~/pandoc_latest/pandoc.deb ~/pandoc_latest/pandoc.tar.gz
tar tf ~/pandoc_latest/pandoc.tar.gz
ls -l ~/pandoc_latest/
curl --help | grep "\-L"
PANDOC_VERSION=2.15; curl -L -o ~/pandoc_latest/pandoc.deb https://github.com/jgm/pandoc/releases/download/${PANDOC_VERSION}/pandoc-${PANDOC_VERSION}-1-amd64.deb
apt-get install ~/pandoc_latest/pandoc.deb 
jobs
vim /project/p2284/docker/Dockerfile 
exit
curl --help
curl --help | grep J
curl --help | grep O
exit
ll
exit
ll 
ll pandoc_latest 
exit
ll pandoc_latest/
exit
cd project/p2284/
make P2284.pdf
apt-get install pandoc-citeproc
apt-get install --help
exit
apt-get --help
apt-get dselect
apt-get dselect-upgrade
exit
cd project/p2284/
make P2284.pdf
rgs "pandoc-citeproc" ./pdf-generator/
cat ./pdf-generator/data/defaults.sh
cat ./pdf-generator/data/defaults.yaml
cat -n ./pdf-generator/data/defaults.yaml 
c
clear
cat -n ./pdf-generator/data/defaults.yaml 
cat -n ./pdf-generator/data/defaults.yaml
cat -n ./pdf-generator/data/defaults.sh
vim ./pdf-generator/data/defaults.sh
ll
make P2284.pdf
vim docker/Dockerfile 
pip install panflute
make P2284.pdf
pip3 install panflute
make P2284.pdf
python3
head "/project/p2284/pdf-generator/data/filters/wg21.py"
#!/usr/bin/env python3
/project/p2284/pdf-generator/data/filters/wg21.py
make P2284.pdf
cat P2284.md 
cat << EOF > p1111.md
---
title: "State Machine"
document: P2284R0
date: today
audience:
    - LEWGI
author:
    - name: Ran Regev
      email: <regev.ran@gmail.com>
toc: true
---
EOF

cat p1111.md 
make p1111.pdf
trancte
rm p1111.md 
cat << EOF > P1111.md
EOF

make P1111.md 
make P1111.pdf
make P1111.html
make P1111.pdf
make VERBOSE=1 P1111.pdf
make VERBOSE=1 P2284.pdf
cat pdf-generator/data/csl.json
vim pdf-generator/data/csl.json
make P2284.pdf
cat pdf-generator/data/csl.json
make P2284.pdf
pandoc P2284.md --citeproc -o generated/P2284.pdf --defaults=pdf-generator/data/defaults.yaml
apt-get install -y xelatex
apt-get search xelatex
apt-cache search xelatex
apt-get install -y texlive-xetex
make P2284.pdf
pandoc P2284.md --citeproc -o generated/P2284.pdf --defaults=pdf-generator/data/defaults.yaml
ll
ll pdf-generator/
cat pdf-generator/P1371R2.md 
make P2284.pdf
pandoc P2284.md --citeproc -o generated/P2284.pdf --defaults=pdf-generator/data/defaults.yaml #--bibliography pdf-generator/data/csl.json
make P2284.pdf
make clean
make P2284.pdf
gs
cd pdf-generator/
gs
git diff -- Makefile
git stash push
gs
cd ..
make P2284.pdf
make clean
make P2284.pdf
exit
