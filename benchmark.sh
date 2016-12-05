cd `dirname $0`

for size in 1024 2048 4096 8192 16384 32768 65536 131072 262144
do
    echo "Page fault $size"
    for trial in 0 1 2
    do
        ./bench-page $size
    done
done

for size in 1024 2048 4096 8192 16384 32768 65536 131072 262144
do
    echo "Baseline $size"
    for trial in 0 1 2
    do
        ./bench-soft $size
    done
done

for size in 1024 2048 4096 8192 16384 32768 65536 131072 262144
do
    echo "DMA $size"
    for trial in 0 1 2
    do
        ./bench-dma $size
    done
done

#poweroff
