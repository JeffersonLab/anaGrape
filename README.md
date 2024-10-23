# anaGrape
tool to run grape-dilepton and twopeg generator and analyze results

it was moved from https://jlabsvn.jlab.org/svnroot/solid/evgen/BH/

## tool to run grape-dilepton generator:

* http://research.kek.jp/people/tabe/grape 
dilepton production generator from electron/positron interacts with proton,used by the experiments at DESY/HERA. 
including Bethe-Heitler, compton and other electroweak dilepton production for elastic,quasi-elastic and DIS process.
similar result comparing to LPAIR, see http://research.kek.jp/people/tabe/grape/heramc1998/proceedings/node4.html#SECTION00040000000000000000

* Read the website including the note and faq. there is also information in its "README" file of the code package

* convert grape output ntuple "grp.rz" or "grp.hbook" to root file "grp.root" by "h2root grp.rz" or "h2root grp.hbook"

Some grape.cards are included here as examples.
The author's ifarm working dir is at /work/solid/zwzhao/BH/grape-dilepton_work

### run using container at jlab ifarm

* module load singularity/3.9.5
* singularity pull docker://wmoore28/grape:1.1
* cp grape.cards_JLab_11_BH_ele_3fold_decaypairelectron_deg5-50 grape.cards (as example)
* singularity exec grape_1.1.sif integ | cat > integ.log   (take a long time like a few hours)
* singularity exec grape_1.1.sif spring | cat  > spring.log
* then a ntuple "grp.hbook" is produced

### run using virtual machine 

* grape-dilepton was written in early 2000 and depends on an older version of cernlib. To repeat its exact environment, I built a redhat7 virtual machine to run it. You can download its [http://www.phy.duke.edu/~zz81/vm/RH7.zip vmware version], then unzip and run it with free vmplayer [http://www.vmware.com/go/downloadplayer] on linux or windows. Or you can download its [http://www.phy.duke.edu/~zz81/vm/RH7.ova virtualbox version], then import and run it with free virtualbox [https://www.virtualbox.org/wiki/Downloads] on linux,window and mac
* The virtual machine only has terminal, Xwindow is not working, so use "ctr+F*" to switch between terminals. both user "zwzhao" and root has password are "111111", 
* The code is under /home/zwzhao/grape-dilpeton_v1.1k ( I had to modify its Makefile to compile it). My work dir is at /home/zwzhao/grape-dilepton_work where you can see some examples. you can use scp to transfer output files to outside of the virtual machine

* "mkdir JLab_11_BH_ele_3fold_decaypairelectron_deg5-50" and "cd JLab_11_BH_ele_3fold_decaypairelectron_deg5-50"
* "cp grape.cards_JLab_11_BH_ele_3fold_decaypairelectron_deg5-50 JLab_11_BH_ele_3fold_decaypairelectron_deg5-50/grape.cards"
* "/home/zwzhao/grape-dilpeton_v1.1k/src/integ | cat > integ.log" (take a long time like a few hours)
* "/home/zwzhao/grape-dilpeton_v1.1k/src/spring | cat > spring.log"
* then a ntuple "grp.rz" is produced. 

### general note 

1. Be careful with NCALL input, too large it can take long time to run bases, too small will reduce accuracy
2. turn ISR on for initial radiation for electron beam. there is no way to make radiation for final state particle of elastic channel yet. (PSFSR doesn't work for this)
3. add "RNDGEN true" in "grape.cards" to use non-default random seed. Otherwise every time, you will re-generate the same events. you need to "mv rndstat.dat rndstat.dat.prev" every time if you want to get new events. This means we can't use grape in farm jobs directly and we have to generate many files first as farm job input. refer to http://research.kek.jp/people/tabe/grape/FAQ/rndstat.html
4. Various cuts like mom and angle etc can be applied in the input file, they can be used carefully to focus the simulation on interested physical region and particular detector acceptance and trigger condition.
5. with interference on for electron pair, the scattering e- and decay e- are not distinguishable. Absolutely NO cut can be applied on any of them without careful consideration, like PMIN,PMAX,THMIN,THMAX,MASSLL etc. A lepton stored in the 8th line has smaller transverse momentum than that of a lepton in the 10th line of the output
6. output has two trees "h1" including event info, refer to http://research.kek.jp/people/tabe/grape/CPC/node8.html
7. total cross section in pb for the simulated phase space,divide it by number of event generated to have the correct weight for each event. It's stored in several places
   (a) tree "h11" including xsec[0]
   (b) section "Convergency Behavior for the Integration Step" of the "integ" log file "bases.result". It's the last iteration of the entry "Estimate(+- Error )order". It's a good idea to check to see these iteration converges.
   (c) display at end of running "spring", thus stored in file "spring.log"
8. when using multiple root files produced with exact same input file, the correct weight factor is (total crossection)/(total event numbers of all files)   
9. Its default +Z axis is along proton beam direction.This applies to Theta angle in input file. To analyze its output in +Z along electron beam direction, we need to do rotation for all particle TLorentzVector by RotateY(TMath::Pi()). if we are using electron beam direction as +Z axis, we need to rotate along Y 180 degree to analyses results
10. Elastic and quasi-elastic (with additional pi0 mass) are ok for proton at rest, but DIS mode doesn't work for proton as rest, refer to https://research.kek.jp/people/tabe/grape/FAQ/patrest.html

### known problem
1. occasionally, integ wouldn't end because grid calculation can't converge for certain configuration. 
2. when producing too many events, spring will crash (weired screen output instead of Cross Section values and file spring.result is empty). you have to reduce NGEN to work. for elastic, 25000000 seems ok. other condition may change it

## tool to run twopeg generator

* two pion exclusive generator at https://github.com/skorodumina/twopeg

at jlab ifarm, run twopeg included in clas12-mcgen 2.14 at /group/clas12/packages/clas12-mcgen/2.14/twopeg

cd /work/halla/solid/zwzhao/twopion/commit7034d9f_20201215/
source /group/clas12/packages/setup.csh
module load clas12/3.4
twopeg  < inp1   (get inp1 example from the source code github)
file "twopeg.dat" in lund format should be produced

## tool to analysis results:

root2lund_grape-dilepton.C to convert "grp.root" to "grp.lund" with vertex info added

ana_grape_twopeg.C can be used to analyze both grape and twopeg output

(outdated) anaGrape.C can be used to analyze grape output

compare.C to compare different histograms

```
prepare to run analysis

(needed for SoLID track smearing)
git clone https://github.com/JeffersonLab/solid_gemc solid_gemc_location
or you can use the existing ifarm location /group/solid/solid_github/JeffersonLab/solid_gemc

git clone https://github.com/JeffersonLab/anaGrape.git
cd anaGrape
ln -s solid_gemc_location/analysis/tracking_resolution ./
ln -s tracking_resolution/res_file ./

```
how to run ana_grape_twopeg.C

(It's too slow to run as script, so better to run after compiling)

The code take input as follows
  void ana_grape_twopeg(string evgen="",string detector="",string input_filedir="",int windex=3,double Ebeam=11,bool Is_res=false,string decaypair="e",int decaymode=0)  
  //windex to select weight, Ebeam to set beam energy
  //Is_res and decaypair are needed for track smearing
  //decaymode are needed for twopeg generator

here are some examples

root 'ana_grape_twopeg.C+("grape","CLAS12","/work/halla/solid/zwzhao/BH/grape-dilepton_work/JLab_11_BH_ele_3fold_decaypairelectron_deg1-50")'

root 'ana_grape_twopeg.C+("grape","SoLID_JPsi","/work/halla/solid/zwzhao/BH/grape-dilepton_work/JLab_11_BH_ele_3fold_decaypairelectron_deg1-50")'

(need more acceptance file to analyze twopeg output, will add later)

root 'ana_grape_twopeg.C+("grape","SoLID_DDVCS_JPsi","/work/halla/solid/zwzhao/BH/grape-dilepton_work/JLab_11_BH_muon_3fold_decaypairelectron_quasi_deg5-50")'

root 'ana_grape_twopeg.C+("grape","SoLID_DDVCS_JPsi","/work/halla/solid/zwzhao/BH/grape-dilepton_work/JLab_11_BH_muon_3fold_decaypairelectron_quasi_deg5-50",11,true,"mu")'

root 'ana_grape_twopeg.C+("twopeg","SoLID_DDVCS_JPsi","/work/halla/solid/zwzhao/twopion/commit7034d9f_20201215/SoLID_JPsi_LH2_e_E11",11,false,"mu",3)'

```
how to run anaGrape.C

cd where_grp.root_is
ln -s where_anaGrape ./
ln -s anaGrape/tracking_resolution/res_file ./
root 'anaGrape/anaGrape.C+("SoLID_JPsi",false)' (It's too slow to run as script, need to run after compiling)

The 1st parameter can be SoLID_JPsi or CLAS12 for detector

The 2nd parameter as true or false to control if the code should smear particle 4-momentum according to SoLID momentum resolution.
```

--------------------

