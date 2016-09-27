if [ -e "${CMSSW_BASE}" ]; then
	#source this script to install the MEM package
	cd $CMSSW_BASE

	#make the MEM install dir
	mkdir -p src/TTH
	cd src/TTH

	#get the MEM code
	git clone https://github.com/jpata/Code.git MEIntegratorStandalone --branch v0.3

	#copy the OpenLoops ME libraries
	cp -R $CMSSW_BASE/src/TTH/MEIntegratorStandalone/libs/* $CMSSW_BASE/lib/$SCRAM_ARCH/

	cd $CMSSW_BASE
fi
