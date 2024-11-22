# Dicas de uso do SDumont

Dicas de uso do SDumont.

## Senha do LNCC

https://novasenhasdumont.lncc.br/

## Workflow

```bash
# 1 - dentro de ~/lncc
sudo vpnc-connect ./sdumont.conf

# 2 - conectado na vpn, pode-se montar
sshfs vitor.curtis3@login.sdumont.lncc.br: ./sdumont-fs/

#
# copiar o que for necessário para ~/lncc/sdumont
#

# 3 - depois basta acessar a máquina
ssh vitor.curtis3@login.sdumont.lncc.br

# 4 - nada funciona em $HOME, deve-se copiar tudo para $SCRATCH
# na máquina remota
cp * $SCRATCH
cd $SCRATCH

# 5 - compilar e executar
make
./Xmit
```

## File System

É possível criar um file system para mover arquivos entre a máquina local e remota com:
`sudo sshfs -o allow_other vitor.curtis@login.sdumont.lncc.br: ~/lncc/sdumont-fs`

É possível montar a pasta SCRATCH diretamente também, através do comando:
`sudo sshfs -o allow_other vitor.curtis@login.sdumont.lncc.br:/scratch/ce2652016/vitor.curtis/ /home/vitor/lncc/sdumont-fs/`

Para desmontar, basta
`sudo umount ~/lncc/sdumont-fs`
