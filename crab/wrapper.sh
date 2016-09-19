#!/bin/bash
set +e
set +v

MD5SUM=`mem.py | md5sum | awk '{print $1}'`
cat <<EOF > fakeprov.txt
Processing History:
 MEM '' '"CMSSW_X_y_Z"' [1]  ($MD5SUM)
EOF

cat <<EOF > $CMSSW_BASE/bin/$SCRAM_ARCH/edmProvDump
#!/bin/sh
cat fakeprov.txt
EOF

chmod +x $CMSSW_BASE/bin/$SCRAM_ARCH/edmProvDump
edmProvDump

python mem.py
cat FrameworkJobReport.xml
