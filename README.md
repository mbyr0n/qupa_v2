xargs -d '\n' -- sudo rm -rfv < install_manifest.txt


sudo rm /usr/local/bin/argos3


sudo rm -rf /usr/local/lib/argos3


sudo rm /usr/local/lib/libargos3*


sudo rm -rf /usr/local/include/argos3


sudo rm -rf /usr/local/share/argos3


sudo rm /usr/local/share/man/man1/argos3.1







cmake -DCMAKE_BUILD_TYPE=Release \
      -DARGOS_BUILD_FOR=simulator \
      -DCMAKE_INSTALL_PREFIX="/usr/local" \
      -DCMAKE_PREFIX_PATH="/usr/local" \
      ../qupa


make -j"$(nproc)



sudo make install
