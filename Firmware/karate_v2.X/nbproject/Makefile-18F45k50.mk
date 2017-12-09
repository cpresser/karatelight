#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-18F45k50.mk)" "nbproject/Makefile-local-18F45k50.mk"
include nbproject/Makefile-local-18F45k50.mk
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=18F45k50
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=cof
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/karate_v2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/karate_v2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/src/usb/usb_device.o ${OBJECTDIR}/src/usb/usb_function_cdc.o ${OBJECTDIR}/src/comm.o ${OBJECTDIR}/src/gamma.o ${OBJECTDIR}/src/tlc5947.o ${OBJECTDIR}/src/usb_descriptors.o ${OBJECTDIR}/src/configbits.o ${OBJECTDIR}/src/karate.o ${OBJECTDIR}/src/usb/usb_fixes.o
POSSIBLE_DEPFILES=${OBJECTDIR}/src/usb/usb_device.o.d ${OBJECTDIR}/src/usb/usb_function_cdc.o.d ${OBJECTDIR}/src/comm.o.d ${OBJECTDIR}/src/gamma.o.d ${OBJECTDIR}/src/tlc5947.o.d ${OBJECTDIR}/src/usb_descriptors.o.d ${OBJECTDIR}/src/configbits.o.d ${OBJECTDIR}/src/karate.o.d ${OBJECTDIR}/src/usb/usb_fixes.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/src/usb/usb_device.o ${OBJECTDIR}/src/usb/usb_function_cdc.o ${OBJECTDIR}/src/comm.o ${OBJECTDIR}/src/gamma.o ${OBJECTDIR}/src/tlc5947.o ${OBJECTDIR}/src/usb_descriptors.o ${OBJECTDIR}/src/configbits.o ${OBJECTDIR}/src/karate.o ${OBJECTDIR}/src/usb/usb_fixes.o


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
	${MAKE} ${MAKE_OPTIONS} -f nbproject/Makefile-18F45k50.mk dist/${CND_CONF}/${IMAGE_TYPE}/karate_v2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=18F45K50
MP_PROCESSOR_OPTION_LD=18f45k50
MP_LINKER_DEBUG_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/src/usb/usb_device.o: src/usb/usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/usb 
	@${RM} ${OBJECTDIR}/src/usb/usb_device.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I"C:/Users/cpresser/_Daten/mplab_workspace/20_KarateLight/karate_v2.X/src" -I"C:/Users/cpresser/_Daten/mplab_workspace/20_KarateLight/karate_v2.X/src/usb" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/src/usb/usb_device.o   src/usb/usb_device.c 
	@${DEP_GEN} -d ${OBJECTDIR}/src/usb/usb_device.o 
	@${FIXDEPS} "${OBJECTDIR}/src/usb/usb_device.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/src/usb/usb_function_cdc.o: src/usb/usb_function_cdc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/usb 
	@${RM} ${OBJECTDIR}/src/usb/usb_function_cdc.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I"C:/Users/cpresser/_Daten/mplab_workspace/20_KarateLight/karate_v2.X/src" -I"C:/Users/cpresser/_Daten/mplab_workspace/20_KarateLight/karate_v2.X/src/usb" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/src/usb/usb_function_cdc.o   src/usb/usb_function_cdc.c 
	@${DEP_GEN} -d ${OBJECTDIR}/src/usb/usb_function_cdc.o 
	@${FIXDEPS} "${OBJECTDIR}/src/usb/usb_function_cdc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/src/comm.o: src/comm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/comm.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I"C:/Users/cpresser/_Daten/mplab_workspace/20_KarateLight/karate_v2.X/src" -I"C:/Users/cpresser/_Daten/mplab_workspace/20_KarateLight/karate_v2.X/src/usb" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/src/comm.o   src/comm.c 
	@${DEP_GEN} -d ${OBJECTDIR}/src/comm.o 
	@${FIXDEPS} "${OBJECTDIR}/src/comm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/src/gamma.o: src/gamma.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/gamma.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I"C:/Users/cpresser/_Daten/mplab_workspace/20_KarateLight/karate_v2.X/src" -I"C:/Users/cpresser/_Daten/mplab_workspace/20_KarateLight/karate_v2.X/src/usb" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/src/gamma.o   src/gamma.c 
	@${DEP_GEN} -d ${OBJECTDIR}/src/gamma.o 
	@${FIXDEPS} "${OBJECTDIR}/src/gamma.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/src/tlc5947.o: src/tlc5947.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/tlc5947.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I"C:/Users/cpresser/_Daten/mplab_workspace/20_KarateLight/karate_v2.X/src" -I"C:/Users/cpresser/_Daten/mplab_workspace/20_KarateLight/karate_v2.X/src/usb" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/src/tlc5947.o   src/tlc5947.c 
	@${DEP_GEN} -d ${OBJECTDIR}/src/tlc5947.o 
	@${FIXDEPS} "${OBJECTDIR}/src/tlc5947.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/src/usb_descriptors.o: src/usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/usb_descriptors.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I"C:/Users/cpresser/_Daten/mplab_workspace/20_KarateLight/karate_v2.X/src" -I"C:/Users/cpresser/_Daten/mplab_workspace/20_KarateLight/karate_v2.X/src/usb" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/src/usb_descriptors.o   src/usb_descriptors.c 
	@${DEP_GEN} -d ${OBJECTDIR}/src/usb_descriptors.o 
	@${FIXDEPS} "${OBJECTDIR}/src/usb_descriptors.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/src/configbits.o: src/configbits.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/configbits.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I"C:/Users/cpresser/_Daten/mplab_workspace/20_KarateLight/karate_v2.X/src" -I"C:/Users/cpresser/_Daten/mplab_workspace/20_KarateLight/karate_v2.X/src/usb" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/src/configbits.o   src/configbits.c 
	@${DEP_GEN} -d ${OBJECTDIR}/src/configbits.o 
	@${FIXDEPS} "${OBJECTDIR}/src/configbits.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/src/karate.o: src/karate.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/karate.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I"C:/Users/cpresser/_Daten/mplab_workspace/20_KarateLight/karate_v2.X/src" -I"C:/Users/cpresser/_Daten/mplab_workspace/20_KarateLight/karate_v2.X/src/usb" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/src/karate.o   src/karate.c 
	@${DEP_GEN} -d ${OBJECTDIR}/src/karate.o 
	@${FIXDEPS} "${OBJECTDIR}/src/karate.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/src/usb/usb_fixes.o: src/usb/usb_fixes.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/usb 
	@${RM} ${OBJECTDIR}/src/usb/usb_fixes.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I"C:/Users/cpresser/_Daten/mplab_workspace/20_KarateLight/karate_v2.X/src" -I"C:/Users/cpresser/_Daten/mplab_workspace/20_KarateLight/karate_v2.X/src/usb" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/src/usb/usb_fixes.o   src/usb/usb_fixes.c 
	@${DEP_GEN} -d ${OBJECTDIR}/src/usb/usb_fixes.o 
	@${FIXDEPS} "${OBJECTDIR}/src/usb/usb_fixes.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
else
${OBJECTDIR}/src/usb/usb_device.o: src/usb/usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/usb 
	@${RM} ${OBJECTDIR}/src/usb/usb_device.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"C:/Users/cpresser/_Daten/mplab_workspace/20_KarateLight/karate_v2.X/src" -I"C:/Users/cpresser/_Daten/mplab_workspace/20_KarateLight/karate_v2.X/src/usb" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/src/usb/usb_device.o   src/usb/usb_device.c 
	@${DEP_GEN} -d ${OBJECTDIR}/src/usb/usb_device.o 
	@${FIXDEPS} "${OBJECTDIR}/src/usb/usb_device.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/src/usb/usb_function_cdc.o: src/usb/usb_function_cdc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/usb 
	@${RM} ${OBJECTDIR}/src/usb/usb_function_cdc.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"C:/Users/cpresser/_Daten/mplab_workspace/20_KarateLight/karate_v2.X/src" -I"C:/Users/cpresser/_Daten/mplab_workspace/20_KarateLight/karate_v2.X/src/usb" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/src/usb/usb_function_cdc.o   src/usb/usb_function_cdc.c 
	@${DEP_GEN} -d ${OBJECTDIR}/src/usb/usb_function_cdc.o 
	@${FIXDEPS} "${OBJECTDIR}/src/usb/usb_function_cdc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/src/comm.o: src/comm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/comm.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"C:/Users/cpresser/_Daten/mplab_workspace/20_KarateLight/karate_v2.X/src" -I"C:/Users/cpresser/_Daten/mplab_workspace/20_KarateLight/karate_v2.X/src/usb" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/src/comm.o   src/comm.c 
	@${DEP_GEN} -d ${OBJECTDIR}/src/comm.o 
	@${FIXDEPS} "${OBJECTDIR}/src/comm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/src/gamma.o: src/gamma.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/gamma.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"C:/Users/cpresser/_Daten/mplab_workspace/20_KarateLight/karate_v2.X/src" -I"C:/Users/cpresser/_Daten/mplab_workspace/20_KarateLight/karate_v2.X/src/usb" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/src/gamma.o   src/gamma.c 
	@${DEP_GEN} -d ${OBJECTDIR}/src/gamma.o 
	@${FIXDEPS} "${OBJECTDIR}/src/gamma.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/src/tlc5947.o: src/tlc5947.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/tlc5947.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"C:/Users/cpresser/_Daten/mplab_workspace/20_KarateLight/karate_v2.X/src" -I"C:/Users/cpresser/_Daten/mplab_workspace/20_KarateLight/karate_v2.X/src/usb" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/src/tlc5947.o   src/tlc5947.c 
	@${DEP_GEN} -d ${OBJECTDIR}/src/tlc5947.o 
	@${FIXDEPS} "${OBJECTDIR}/src/tlc5947.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/src/usb_descriptors.o: src/usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/usb_descriptors.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"C:/Users/cpresser/_Daten/mplab_workspace/20_KarateLight/karate_v2.X/src" -I"C:/Users/cpresser/_Daten/mplab_workspace/20_KarateLight/karate_v2.X/src/usb" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/src/usb_descriptors.o   src/usb_descriptors.c 
	@${DEP_GEN} -d ${OBJECTDIR}/src/usb_descriptors.o 
	@${FIXDEPS} "${OBJECTDIR}/src/usb_descriptors.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/src/configbits.o: src/configbits.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/configbits.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"C:/Users/cpresser/_Daten/mplab_workspace/20_KarateLight/karate_v2.X/src" -I"C:/Users/cpresser/_Daten/mplab_workspace/20_KarateLight/karate_v2.X/src/usb" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/src/configbits.o   src/configbits.c 
	@${DEP_GEN} -d ${OBJECTDIR}/src/configbits.o 
	@${FIXDEPS} "${OBJECTDIR}/src/configbits.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/src/karate.o: src/karate.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/karate.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"C:/Users/cpresser/_Daten/mplab_workspace/20_KarateLight/karate_v2.X/src" -I"C:/Users/cpresser/_Daten/mplab_workspace/20_KarateLight/karate_v2.X/src/usb" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/src/karate.o   src/karate.c 
	@${DEP_GEN} -d ${OBJECTDIR}/src/karate.o 
	@${FIXDEPS} "${OBJECTDIR}/src/karate.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/src/usb/usb_fixes.o: src/usb/usb_fixes.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/usb 
	@${RM} ${OBJECTDIR}/src/usb/usb_fixes.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"C:/Users/cpresser/_Daten/mplab_workspace/20_KarateLight/karate_v2.X/src" -I"C:/Users/cpresser/_Daten/mplab_workspace/20_KarateLight/karate_v2.X/src/usb" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/src/usb/usb_fixes.o   src/usb/usb_fixes.c 
	@${DEP_GEN} -d ${OBJECTDIR}/src/usb/usb_fixes.o 
	@${FIXDEPS} "${OBJECTDIR}/src/usb/usb_fixes.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/karate_v2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE) "src\rm18f45k50 - MCHPUSB Bootload.lkr"  -p$(MP_PROCESSOR_OPTION_LD)  -w -x -u_DEBUG -m"$(BINDIR_)$(TARGETBASE).map" -w -l"C:/Program Files (x86)/Microchip/mplabc18/v3.47/lib"  -z__MPLAB_BUILD=1  -u_CRUNTIME -z__MPLAB_DEBUG=1 -z__MPLAB_DEBUGGER_ICD3=1 $(MP_LINKER_DEBUG_OPTION) -l ${MP_CC_DIR}\\..\\lib  -o dist/${CND_CONF}/${IMAGE_TYPE}/karate_v2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}   
else
dist/${CND_CONF}/${IMAGE_TYPE}/karate_v2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE) "src\rm18f45k50 - MCHPUSB Bootload.lkr"  -p$(MP_PROCESSOR_OPTION_LD)  -w  -m"$(BINDIR_)$(TARGETBASE).map" -w -l"C:/Program Files (x86)/Microchip/mplabc18/v3.47/lib"  -z__MPLAB_BUILD=1  -u_CRUNTIME -l ${MP_CC_DIR}\\..\\lib  -o dist/${CND_CONF}/${IMAGE_TYPE}/karate_v2.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}   
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/18F45k50
	${RM} -r dist/18F45k50

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
