ARG ESP_IDF_VERSION=v6.0.2
FROM espressif/idf:${ESP_IDF_VERSION}

ENV LANG=C.UTF-8
ENV LC_ALL=C.UTF-8

WORKDIR /ws

# source the esp idf
RUN echo 'source "$IDF_PATH/export.sh"' >> /root/.bashrc