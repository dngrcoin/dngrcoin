[Unit]
Description=DNGRcoin's distributed currency daemon
After=network.target

[Service]
User=dngrcoin
Group=dngrcoin

Type=forking
PIDFile=/var/lib/dngrcoind/dngrcoind.pid
ExecStart=/usr/bin/dngrcoind -daemon -pid=/var/lib/dngrcoind/dngrcoind.pid \
-conf=/etc/dngrcoin/dngrcoin.conf -datadir=/var/lib/dngrcoind -disablewallet

Restart=always
PrivateTmp=true
TimeoutStopSec=60s
TimeoutStartSec=2s
StartLimitInterval=120s
StartLimitBurst=5

[Install]
WantedBy=multi-user.target
