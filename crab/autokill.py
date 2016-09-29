import sys
import subprocess

crabProjectList = sys.argv[1:]

for icp in crabProjectList:
    subprocess.call(["crab kill "+icp],shell=True)
  
  #exit(0)
  #crab resubmit --maxmemory=2500 --siteblacklist=T2_US_Florida,T2_US_UCSD,T2_US_Wisconsin,T2_US_Nebraska crab_ttbar_incl_ICHEP0
