
# Compilación del paquete
´´´
cd ~/qupa_v2
mkdir -p build && cd build
cmake -DCMAKE_BUILD_TYPE=Release \
      -DARGOS_BUILD_FOR=simulator \
      -DCMAKE_INSTALL_PREFIX="/usr/local" \
      -DCMAKE_PREFIX_PATH="/usr/local" \
      ../qupa
make -j"$(nproc)
sudo make install

´´´
