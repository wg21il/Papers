
FROM ubuntu:latest

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
	curl \
	gcc \
	git \
	make \
	pandoc \
	pandoc-citeproc \
	pip \
	python \
	python3 \
	python3.8-venv \
	texlive-xetex \
	vim 

ENV PANDOC_VERSION=2.15
ENV PANDOC_PATH=/pandoc_latest
ENV PANDOC_FILE=pandoc-${PANDOC_VERSION}-1-amd64.deb 
ADD https://github.com/jgm/pandoc/releases/download/${PANDOC_VERSION}/${PANDOC_FILE} /${PANDOC_PATH}/
RUN apt-get install -y ${PANDOC_PATH}/${PANDOC_FILE}

RUN pip install panflute
