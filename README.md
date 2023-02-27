# anaGrape
tool to run grape-dilepton generator and analyze results

it is moved from https://jlabsvn.jlab.org/svnroot/solid/evgen/BH/

## tool to run generator:

### grape-dilepton generator
* http://research.kek.jp/people/tabe/grape
dilepton production generator from electron interacts with proton,used by the experiments at DESY/HERA
including Bethe-Heitler, compton and other electroweak dilepton production
similar result comparing to LPAIR, see http://research.kek.jp/people/tabe/grape/heramc1998/proceedings/node4.html#SECTION00040000000000000000

### virtual machine 

* It was written in early 2000 and depends on an older version of cernlib. To repeat its exact environment, I built a redhat7 virtual machine to run it. You can download its [http://www.phy.duke.edu/~zz81/vm/RH7.zip vmware version], then unzip and run it with free vmplayer [http://www.vmware.com/go/downloadplayer] on linux or windows. Or you can't download its [http://www.phy.duke.edu/~zz81/vm/RH7.ova virtualbox version], then import and run it with free virtualbox [https://www.virtualbox.org/wiki/Downloads] on linux,mac,window
* The virtual machine only has terminal, Xwindow is not working, so use "ctr+F*" to swtich between terminals. both user "zwzhao" and root has passwrod "111111", 
The code is under /home/zwzhao/grape-dilpeton_v1.1k ( I had to modify its makefile to compile it)
My work dir is at /home/zwzhao/grape-dilepton_work where you can see some examples
you can use scp to transfer files within the virtual machine to outside

### how to run it

* Read the code website and its "README" file to understand how its input parameters defined in "grape.cards" and how to run it. 
* "mkdir JLab_11_BH_ele_3fold_decaypairelectron_deg5-50" and "cd JLab_11_BH_ele_3fold_decaypairelectron_deg5-50"
* "cp grape.cards_JLab_11_BH_ele_3fold_decaypairelectron_deg5-50 JLab_11_BH_ele_3fold_decaypairelectron_deg5-50/grape.cards"
* "/home/zwzhao/grape-dilpeton_v1.1k/src/integ | cat > integ.log" (take a long time like 10 hours)
* "/home/zwzhao/grape-dilpeton_v1.1k/src/spring | cat > spring.log"
* then a ntuple "grp.rz" is produced. 

module load singularity/3.9.5
singularity exec ../../grape_1.1.sif integ

### general note 

0. Be careful with NCALL input, too large it can take long time to run bases, too small will reduce accuracy
1. turn ISR on for initial radiation for electron beam. there is no way to make radation forr final state particle of elastic channel yet. (PSFSR doesn't work for this)
2. add "RNDGEN true" in grape.cards" to use non-default random seed. Otherwise everytime, you will regeneated the same events. you need to "mv rndstat.dat rndstat.dat.prev" everytime if you want to get new events. refer to http://research.kek.jp/people/tabe/grape/FAQ/rndstat.html
3. Variaous cuts like mom and angle etc can be applied in the input file, they can be used carefully to focus the simulation on interested physical region and particular detecctor acceptance and trigger condition.
4. with interference on for electrion pair, the scattering e- and decay e- are not distinguishable. Absolutely NO cut can be applied on any of them without careful consideration, like PMIN,PMAX,THMIN,THMAX,MASSLL etc.
5. with interference on for electrion pair, a lepton stored in the 8th line has smaller transverse momentum than that of a lepton in the 10th line of the output
6. output has two trees "h1" including event info, refer to http://research.kek.jp/people/tabe/grape/CPC/node8.html
7. total crossection in pb for the simulated phasespace,divide it by number of event generated to have the correct weight for each event. It's stored in several places
   (a) tree "h11" including xsec[0]
   (b) section "Convergency Behavior for the Integration Step" of the "integ" log file "bases.result". It's the last iteration of the entry "Estimate(+- Error )order". It's a good idea to check to see these iteration converges.
   (c) display at end of running "spring", thus stored in file "spring.log"
8. It's default +Z axis is along proton beam direction. So is Theta defined in its input file
if we are using electron beam direction as +Z axis, we need to rotate along Y 180 degree to analyses results
9. when using multiple root files, the correct weight factor is (total crossection)/(total event numbers of all files)

### known problem
1. occasionally, integ wouldn't end because grid calculation can't converge for certain configuration. 
2. spring will crash when events go more than 2.9M due to unknown reason (maybe related to avalaible mem). so set NGEN at most 25000000 to be safe

## tool to analysis results:

convert ntuple "grp.rz" to root file "grp.root" by "h2root grp.rz"

anaGrape.C can be used to analyze the output tree "grp.root" from grape-dilepton

acceptance file and resolution file are needed for anaGrape.C to work

```
here is how to run it

git clone https://github.com/JeffersonLab/anaGrape.git
cd anaGrape
wget https://github.com/JeffersonLab/solid_gemc/raw/master/analysis/acceptance/result_JPsi/201501/acceptance_solid_JPsi_electron_target315_output.root
wget https://solid.jlab.org/files/sim/tmp/ddvcs/acceptance_solid_DDVCS_JPsi_LH2_full_muonm_1e6_output_4thFAMD_1stLAMD.root

download the dir below somewhere
https://github.com/JeffersonLab/solid_gemc/tree/master/analysis/tracking_resolution
then make a link by "ln -s the_dir tracking_resolution ./"

mkdir JLab_11_BH_ele_3fold_decaypairelectron_deg5-50
cd JLab_11_BH_ele_3fold_decaypairelectron_deg5-50
cp where_it_is/grp.rz ./
h2root grp.rz
ln -s where_anaGrape ./
ln -s anaGrape/tracking_resolution/res_file ./
root 'anaGrape/anaGrape.C+("SoLID_DDVCS_JPsi",false)' (It's too slow to run as script, need to run after compiling)

The 1st parameter can be SoLID or CLAS12 for detector

The 2nd parameter as true or false to control if the code should smear particle 4-momentum according to SoLID momentum resolution.
```

root2lund_grape-dilepton.C to convert "grp.root" to "grp.lund" with vertex info added
root -b -q 'root2lund_grape-dilepton.C+' (It's too slow and use too much mem to run as script, need to run after compiling)

compare.C to compare different configuration

--------------------
