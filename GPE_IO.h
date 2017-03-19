// These functions perform data transfer from (to) files that are produced (processed) in MATLAB.
int create_filenames(char filenameFilenames[],char filenameSystemParameters[],
		     char filenameBaseOrderParameters[]);
// The MATLAB routune that initializes the system gives back a file (filenameFilenames), that
// contains the names of all the other necessary files for the GPE algorithm. 
// These are the other ones in the argument list of this function.

int load_SystemParameters(char filenameSystemParameters[],System_Parameters& sysparams);
// Loads the text file 'filenameSystemParameters', that had been generated by a MATLAB routine.
// NOTE: this function allocates the array 'sysparams.saving_times[]' of length 
//       'sysparams.length_saving_times_array'. This can be freed by the function 
//       'free_SystemParameters()' in file GPE_allocations.cpp.

int loadParameterDouble(FILE* fp,char filenameSystemParameters[],char nameOfParameter[],double* parameterPtr);
int loadParameterInt   (FILE* fp,char filenameSystemParameters[],char nameOfParameter[],int*    parameterPtr);
// Short routines used only by load_SystemParameters().

int findParameterInFile(FILE* fp,char nameOfParameter[],char valueOfParameterString[]);
// Finds the variable 'nameOfParameter' between the characters '=' and ',' in file 'fp'.
// The variable's value is put into 'valueOfParameterString' in string form.

void initializePsisAndGPE(GPE_Parameters& gpe,System_Parameters sysparams,GPE_Psis &Psis);
// Sets initial conditions for Psis and fills up the array gpe.EXP.

int load_initial_GPE_Psis(char filenameInitialConditions[],GPE_Psis& Psis,System_Parameters sysparams);
// Loads the initial values of the GPE, that has been formerly generated by a MATLAB routine.
// The order parameters (Psi1,Psi2 and Psi3) are stored in the data file 'filenameInitialConditions'
// as a string of 'double' numbers. 
// The data is ordered as: RePsi1[1...sysparams.M], ImPsi1[1...sysparams.M], 
//                         RePsi2[1...sysparams.M], ImPsi2[1...sysparams.M],
//                         RePsi3[1...sysparams.M], ImPsi3[1...sysparams.M].

int save_Psis(const char filename[],GPE_Psis Psis,GPE_Parameters gpe,System_Parameters sysparams,FFTW_Struct FFTW_Variables);
// Saving method: put the real and imaginary parts of the order parameters and densities
// in a consecutive manner: [RePsi1,ImPsi1,RePsi2,ImPsi2,RePsi3,ImPsi3,
//                           Re_n11,Re_n12,Im_n12,Re_n13,Im_n13,Re_n22,Re_n23,Im_n23,Re_n33,
//                           Re_nTOF11,Re_nTOF12,Im_nTOF12,Re_nTOF13,Im_nTOF13,Re_nTOF22,Re_nTOF23,Im_nTOF23,Re_nTOF33,
//                           RePhiAverage1,ImPhiAverage1,RePhiAverage2,ImPhiAverage2,RePhiAverage3,ImPhiAverage3].
// The reason for this strange solution is that MATLAB can read data in a consecutive manner.
// Note: throughout the saving prcess we use the arrays  Psis.PsiI1, Psis.PsiI2, Psis.PsiI3,
// Psis.PsiK1, Psis.PsiK2 and Psis.PsiK3 to store temporary arrays of data. 
// Since Psis.PsiI-s and Psis.PsiK-s are used only in the GPE iterations as auxiliary arrays one can do this safely.

void reset_dt(GPE_Parameters gpe,System_Parameters& sysparams,GPE_Psis Psis,FFTW_Struct FFTW_Variables);
// Redefines the timestep in the GPE iteration as:
// dt = 0.02* |\Sum dS/dPsi_i * Psi_i^*| / \Sum |Psi_i|^2.
// So with our 4th order method the error will be in the order of 0.02^4=1.6e-7 per step.

void saveSystemParameters(char filenameSystemParameters[],System_Parameters sysparams);
// Saves sysparams into the file filenamSystemParameters. 

void addRandomNoise(GPE_Psis Psis,GPE_Parameters gpe,System_Parameters sysparams);
// At given times (sysparams.addNoiseTimes) it adds a random noise to the Psis using 
// the function noise().

void noise(GPE_Psis Psis,int noOfFreqs,double *maxFreqRate,double *randomnessRate,System_Parameters sysparams);
// Adds a random noise to Psis.Psi1,Psis.Psi2 and Psis.Psi3. 
// Since Psis.PsiKk and Psis.PsiIk (k=1,2,3) are auxiliary variables, they don't have to be modified here.
// The iteration cycle of the GPE solver routine uses only the values of Psis.Psik as inputs.
// Algorithm:
// Psis.Psik += amplitude*exp(i*(freqx*jx+freqy*jy+freqz*jz))
// noOfFreqs: the number of times this random part will be added at randomly chosen quasimomenta (freqx,freqy,freqz).
// maxFreqRate[3]: the random frequencies will come from an interval width endpoints at 
//                 +-maxFreqRate[k]*(the maximal possible quasimomentum)
// randomnessRate: amplitude=randomnessRate[k]*|Psis.Psik|_2