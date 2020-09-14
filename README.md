# IF4031_2020_T01_K01_G09

## Hasil Benchmark Web Server NGINX dan Apache 

### NGINX
**File 500B**
![nginx_500B_benchmark](images/nginx_500B_benchmark.png)

![nginx_500B_benchmark](images/nginx_500B_memory.png)

**File 20kB**
![nginx_20kB_benchmark](images/nginx_20kB_benchmark.png)

![nginx_20kB_benchmark](images/nginx_20kB_memory.png)

### Apache

**File 500B**
![apache_500B_benchmark](images/apache_500B_benchmark.png)

![apache_500B_benchmark](images/apache_500B_memory.png)

**File 20kB**
![apache_20kB_benchmark](images/apache_20kB_benchmark.png)

![apache_20kB_benchmark](images/apache_20kB_memory.png)

## Web Server dengan Low Level Library

### Building & Cara Menjalankan Program

*Low Level library* yang kami gunakan untuk membuat web server adalah **Libevent** . Berikut ini adalah cara menjalankan programnya :
1. clone project ini
2. `cd` ke folder project
3. `mkdir build` untuk membuat directory build
4. `cd build`
5. `cmake ..` (pastikan cmake sudah terinstall dalam sistem)
6. `make` (pastikan library libevent sudah terinstall)
7. `./webserver <PORT> <FILEPATH>`

### Hasil Testing

TBD

## Web Server dengan High Level Library

### Building & Cara Menjalankan Program

*High Level Library* yang kami gunakan untuk membuat web server adalah **Node JS** . Berikut ini adalah cara menjalankan programnya : 
1. clone project ini
2. `cd` ke folder project
3. jalankan `node server_high.js <PORT> <FILEPATH>`

### Hasil Testing

**File 500B**
![high_level_500B_benchmark](images/high_level_500B_benchmark.png)

![high_level_500B_benchmark](images/high_level_500B_memory.png)

**File 20kB**
![high_level_20kB_benchmark](images/high_level_20kB_benchmark.png)

![high_level_20kB_benchmark](images/high_level_20kB_memory.png)

