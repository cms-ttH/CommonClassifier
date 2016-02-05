if [ -e "${CMSSW_BASE}" ]; then
	#source this script to install the MEM package
	cd $CMSSW_BASE

	#make the MEM install dir
	mkdir -p src/TTH
	cd src/TTH

	#get the MEM code
	git clone https://github.com/bianchini/Code.git MEIntegratorStandalone

	#copy the OpenLoops ME libraries
	cp $CMSSW_BASE/src/TTH/MEIntegratorStandalone/libs/*.so $CMSSW_BASE/lib/$SCRAM_ARCH/

	cd $CMSSW_BASE
fi
