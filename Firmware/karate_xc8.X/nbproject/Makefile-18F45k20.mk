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
ifeq "$(wildcard nbproject/Makefile-local-18F45k20.mk)" "nbproject/Makefile-local-18F45k20.mk"
include nbproject/Makefile-local-18F45k20.mk
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=18F45k20
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=cof
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/karate_xc8.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/karate_xc8.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1810352431/usb_device.p1 ${OBJECTDIR}/_ext/1810352431/usb_device_cdc.p1 ${OBJECTDIR}/_ext/1810352431/usb_descriptors.p1 ${OBJECTDIR}/_ext/1056981605/gamma.p1 ${OBJECTDIR}/_ext/1056981605/karate.p1 ${OBJECTDIR}/_ext/1056981605/tlc5947.p1 ${OBJECTDIR}/_ext/1056981605/configbits.p1 ${OBJECTDIR}/_ext/1056981605/comm.p1 ${OBJECTDIR}/_ext/1056981605/usb_hal_fixes.p1
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1810352431/usb_device.p1.d ${OBJECTDIR}/_ext/1810352431/usb_device_cdc.p1.d ${OBJECTDIR}/_ext/1810352431/usb_descriptors.p1.d ${OBJECTDIR}/_ext/1056981605/gamma.p1.d ${OBJECTDIR}/_ext/1056981605/karate.p1.d ${OBJECTDIR}/_ext/1056981605/tlc5947.p1.d ${OBJECTDIR}/_ext/1056981605/configbits.p1.d ${OBJECTDIR}/_ext/1056981605/comm.p1.d ${OBJECTDIR}/_ext/1056981605/usb_hal_fixes.p1.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1810352431/usb_device.p1 ${OBJECTDIR}/_ext/1810352431/usb_device_cdc.p1 ${OBJECTDIR}/_ext/1810352431/usb_descriptors.p1 ${OBJECTDIR}/_ext/1056981605/gamma.p1 ${OBJECTDIR}/_ext/1056981605/karate.p1 ${OBJECTDIR}/_ext/1056981605/tlc5947.p1 ${OBJECTDIR}/_ext/1056981605/configbits.p1 ${OBJECTDIR}/_ext/1056981605/comm.p1 ${OBJECTDIR}/_ext/1056981605/usb_hal_fixes.p1


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
	${MAKE} ${MAKE_OPTIONS} -f nbproject/Makefile-18F45k20.mk dist/${CND_CONF}/${IMAGE_TYPE}/karate_xc8.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=18F45K20
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1810352431/usb_device.p1: C:/Users/cpresser/_Daten/mplab_workspace/20_KarateLight/karate_xc8.X/src/usb/src/usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1810352431 
	@${RM} ${OBJECTDIR}/_ext/1810352431/usb_device.p1.d 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G --asmlist  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug,9 --addrqual=require --mode=pro -P -N255 -I"src" -I"../../../../../../Program Files (x86)/Microchip/xc8/v1.34/include" --warn=0 --summary=default,-psect,-class,+mem,-hex,-file --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,-download,-stackcall,+config,+clib,+plib "--errformat=%%f:%%l: error: %%s" "--warnformat=%%f:%%l: warning: %%s" "--msgformat=%%f:%%l: advisory: %%s"  -o${OBJECTDIR}/_ext/1810352431/usb_device.p1  C:/Users/cpresser/_Daten/mplab_workspace/20_KarateLight/karate_xc8.X/src/usb/src/usb_device.c 
	@-${MV} ${OBJECTDIR}/_ext/1810352431/usb_device.d ${OBJECTDIR}/_ext/1810352431/usb_device.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1810352431/usb_device.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1810352431/usb_device_cdc.p1: C:/Users/cpresser/_Daten/mplab_workspace/20_KarateLight/karate_xc8.X/src/usb/src/usb_device_cdc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1810352431 
	@${RM} ${OBJECTDIR}/_ext/1810352431/usb_device_cdc.p1.d 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G --asmlist  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug,9 --addrqual=require --mode=pro -P -N255 -I"src" -I"../../../../../../Program Files (x86)/Microchip/xc8/v1.34/include" --warn=0 --summary=default,-psect,-class,+mem,-hex,-file --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,-download,-stackcall,+config,+clib,+plib "--errformat=%%f:%%l: error: %%s" "--warnformat=%%f:%%l: warning: %%s" "--msgformat=%%f:%%l: advisory: %%s"  -o${OBJECTDIR}/_ext/1810352431/usb_device_cdc.p1  C:/Users/cpresser/_Daten/mplab_workspace/20_KarateLight/karate_xc8.X/src/usb/src/usb_device_cdc.c 
	@-${MV} ${OBJECTDIR}/_ext/1810352431/usb_device_cdc.d ${OBJECTDIR}/_ext/1810352431/usb_device_cdc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1810352431/usb_device_cdc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1810352431/usb_descriptors.p1: C:/Users/cpresser/_Daten/mplab_workspace/20_KarateLight/karate_xc8.X/src/usb/src/usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1810352431 
	@${RM} ${OBJECTDIR}/_ext/1810352431/usb_descriptors.p1.d 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G --asmlist  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug,9 --addrqual=require --mode=pro -P -N255 -I"src" -I"../../../../../../Program Files (x86)/Microchip/xc8/v1.34/include" --warn=0 --summary=default,-psect,-class,+mem,-hex,-file --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,-download,-stackcall,+config,+clib,+plib "--errformat=%%f:%%l: error: %%s" "--warnformat=%%f:%%l: warning: %%s" "--msgformat=%%f:%%l: advisory: %%s"  -o${OBJECTDIR}/_ext/1810352431/usb_descriptors.p1  C:/Users/cpresser/_Daten/mplab_workspace/20_KarateLight/karate_xc8.X/src/usb/src/usb_descriptors.c 
	@-${MV} ${OBJECTDIR}/_ext/1810352431/usb_descriptors.d ${OBJECTDIR}/_ext/1810352431/usb_descriptors.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1810352431/usb_descriptors.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1056981605/gamma.p1: C:/Users/cpresser/_Daten/mplab_workspace/20_KarateLight/karate_xc8.X/src/gamma.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1056981605 
	@${RM} ${OBJECTDIR}/_ext/1056981605/gamma.p1.d 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G --asmlist  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug,9 --addrqual=require --mode=pro -P -N255 -I"src" -I"../../../../../../Program Files (x86)/Microchip/xc8/v1.34/include" --warn=0 --summary=default,-psect,-class,+mem,-hex,-file --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,-download,-stackcall,+config,+clib,+plib "--errformat=%%f:%%l: error: %%s" "--warnformat=%%f:%%l: warning: %%s" "--msgformat=%%f:%%l: advisory: %%s"  -o${OBJECTDIR}/_ext/1056981605/gamma.p1  C:/Users/cpresser/_Daten/mplab_workspace/20_KarateLight/karate_xc8.X/src/gamma.c 
	@-${MV} ${OBJECTDIR}/_ext/1056981605/gamma.d ${OBJECTDIR}/_ext/1056981605/gamma.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1056981605/gamma.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1056981605/karate.p1: C:/Users/cpresser/_Daten/mplab_workspace/20_KarateLight/karate_xc8.X/src/karate.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1056981605 
	@${RM} ${OBJECTDIR}/_ext/1056981605/karate.p1.d 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G --asmlist  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug,9 --addrqual=require --mode=pro -P -N255 -I"src" -I"../../../../../../Program Files (x86)/Microchip/xc8/v1.34/include" --warn=0 --summary=default,-psect,-class,+mem,-hex,-file --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,-download,-stackcall,+config,+clib,+plib "--errformat=%%f:%%l: error: %%s" "--warnformat=%%f:%%l: warning: %%s" "--msgformat=%%f:%%l: advisory: %%s"  -o${OBJECTDIR}/_ext/1056981605/karate.p1  C:/Users/cpresser/_Daten/mplab_workspace/20_KarateLight/karate_xc8.X/src/karate.c 
	@-${MV} ${OBJECTDIR}/_ext/1056981605/karate.d ${OBJECTDIR}/_ext/1056981605/karate.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1056981605/karate.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1056981605/tlc5947.p1: C:/Users/cpresser/_Daten/mplab_workspace/20_KarateLight/karate_xc8.X/src/tlc5947.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1056981605 
	@${RM} ${OBJECTDIR}/_ext/1056981605/tlc5947.p1.d 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G --asmlist  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug,9 --addrqual=require --mode=pro -P -N255 -I"src" -I"../../../../../../Program Files (x86)/Microchip/xc8/v1.34/include" --warn=0 --summary=default,-psect,-class,+mem,-hex,-file --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,-download,-stackcall,+config,+clib,+plib "--errformat=%%f:%%l: error: %%s" "--warnformat=%%f:%%l: warning: %%s" "--msgformat=%%f:%%l: advisory: %%s"  -o${OBJECTDIR}/_ext/1056981605/tlc5947.p1  C:/Users/cpresser/_Daten/mplab_workspace/20_KarateLight/karate_xc8.X/src/tlc5947.c 
	@-${MV} ${OBJECTDIR}/_ext/1056981605/tlc5947.d ${OBJECTDIR}/_ext/1056981605/tlc5947.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1056981605/tlc5947.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1056981605/configbits.p1: C:/Users/cpresser/_Daten/mplab_workspace/20_KarateLight/karate_xc8.X/src/configbits.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1056981605 
	@${RM} ${OBJECTDIR}/_ext/1056981605/configbits.p1.d 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G --asmlist  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug,9 --addrqual=require --mode=pro -P -N255 -I"src" -I"../../../../../../Program Files (x86)/Microchip/xc8/v1.34/include" --warn=0 --summary=default,-psect,-class,+mem,-hex,-file --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,-download,-stackcall,+config,+clib,+plib "--errformat=%%f:%%l: error: %%s" "--warnformat=%%f:%%l: warning: %%s" "--msgformat=%%f:%%l: advisory: %%s"  -o${OBJECTDIR}/_ext/1056981605/configbits.p1  C:/Users/cpresser/_Daten/mplab_workspace/20_KarateLight/karate_xc8.X/src/configbits.c 
	@-${MV} ${OBJECTDIR}/_ext/1056981605/configbits.d ${OBJECTDIR}/_ext/1056981605/configbits.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1056981605/configbits.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1056981605/comm.p1: C:/Users/cpresser/_Daten/mplab_workspace/20_KarateLight/karate_xc8.X/src/comm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1056981605 
	@${RM} ${OBJECTDIR}/_ext/1056981605/comm.p1.d 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G --asmlist  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug,9 --addrqual=require --mode=pro -P -N255 -I"src" -I"../../../../../../Program Files (x86)/Microchip/xc8/v1.34/include" --warn=0 --summary=default,-psect,-class,+mem,-hex,-file --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,-download,-stackcall,+config,+clib,+plib "--errformat=%%f:%%l: error: %%s" "--warnformat=%%f:%%l: warning: %%s" "--msgformat=%%f:%%l: advisory: %%s"  -o${OBJECTDIR}/_ext/1056981605/comm.p1  C:/Users/cpresser/_Daten/mplab_workspace/20_KarateLight/karate_xc8.X/src/comm.c 
	@-${MV} ${OBJECTDIR}/_ext/1056981605/comm.d ${OBJECTDIR}/_ext/1056981605/comm.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1056981605/comm.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1056981605/usb_hal_fixes.p1: C:/Users/cpresser/_Daten/mplab_workspace/20_KarateLight/karate_xc8.X/src/usb_hal_fixes.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1056981605 
	@${RM} ${OBJECTDIR}/_ext/1056981605/usb_hal_fixes.p1.d 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G --asmlist  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug,9 --addrqual=require --mode=pro -P -N255 -I"src" -I"../../../../../../Program Files (x86)/Microchip/xc8/v1.34/include" --warn=0 --summary=default,-psect,-class,+mem,-hex,-file --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,-download,-stackcall,+config,+clib,+plib "--errformat=%%f:%%l: error: %%s" "--warnformat=%%f:%%l: warning: %%s" "--msgformat=%%f:%%l: advisory: %%s"  -o${OBJECTDIR}/_ext/1056981605/usb_hal_fixes.p1  C:/Users/cpresser/_Daten/mplab_workspace/20_KarateLight/karate_xc8.X/src/usb_hal_fixes.c 
	@-${MV} ${OBJECTDIR}/_ext/1056981605/usb_hal_fixes.d ${OBJECTDIR}/_ext/1056981605/usb_hal_fixes.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1056981605/usb_hal_fixes.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/_ext/1810352431/usb_device.p1: C:/Users/cpresser/_Daten/mplab_workspace/20_KarateLight/karate_xc8.X/src/usb/src/usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1810352431 
	@${RM} ${OBJECTDIR}/_ext/1810352431/usb_device.p1.d 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G --asmlist  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug,9 --addrqual=require --mode=pro -P -N255 -I"src" -I"../../../../../../Program Files (x86)/Microchip/xc8/v1.34/include" --warn=0 --summary=default,-psect,-class,+mem,-hex,-file --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,-download,-stackcall,+config,+clib,+plib "--errformat=%%f:%%l: error: %%s" "--warnformat=%%f:%%l: warning: %%s" "--msgformat=%%f:%%l: advisory: %%s"  -o${OBJECTDIR}/_ext/1810352431/usb_device.p1  C:/Users/cpresser/_Daten/mplab_workspace/20_KarateLight/karate_xc8.X/src/usb/src/usb_device.c 
	@-${MV} ${OBJECTDIR}/_ext/1810352431/usb_device.d ${OBJECTDIR}/_ext/1810352431/usb_device.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1810352431/usb_device.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1810352431/usb_device_cdc.p1: C:/Users/cpresser/_Daten/mplab_workspace/20_KarateLight/karate_xc8.X/src/usb/src/usb_device_cdc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1810352431 
	@${RM} ${OBJECTDIR}/_ext/1810352431/usb_device_cdc.p1.d 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G --asmlist  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug,9 --addrqual=require --mode=pro -P -N255 -I"src" -I"../../../../../../Program Files (x86)/Microchip/xc8/v1.34/include" --warn=0 --summary=default,-psect,-class,+mem,-hex,-file --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,-download,-stackcall,+config,+clib,+plib "--errformat=%%f:%%l: error: %%s" "--warnformat=%%f:%%l: warning: %%s" "--msgformat=%%f:%%l: advisory: %%s"  -o${OBJECTDIR}/_ext/1810352431/usb_device_cdc.p1  C:/Users/cpresser/_Daten/mplab_workspace/20_KarateLight/karate_xc8.X/src/usb/src/usb_device_cdc.c 
	@-${MV} ${OBJECTDIR}/_ext/1810352431/usb_device_cdc.d ${OBJECTDIR}/_ext/1810352431/usb_device_cdc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1810352431/usb_device_cdc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1810352431/usb_descriptors.p1: C:/Users/cpresser/_Daten/mplab_workspace/20_KarateLight/karate_xc8.X/src/usb/src/usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1810352431 
	@${RM} ${OBJECTDIR}/_ext/1810352431/usb_descriptors.p1.d 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G --asmlist  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug,9 --addrqual=require --mode=pro -P -N255 -I"src" -I"../../../../../../Program Files (x86)/Microchip/xc8/v1.34/include" --warn=0 --summary=default,-psect,-class,+mem,-hex,-file --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,-download,-stackcall,+config,+clib,+plib "--errformat=%%f:%%l: error: %%s" "--warnformat=%%f:%%l: warning: %%s" "--msgformat=%%f:%%l: advisory: %%s"  -o${OBJECTDIR}/_ext/1810352431/usb_descriptors.p1  C:/Users/cpresser/_Daten/mplab_workspace/20_KarateLight/karate_xc8.X/src/usb/src/usb_descriptors.c 
	@-${MV} ${OBJECTDIR}/_ext/1810352431/usb_descriptors.d ${OBJECTDIR}/_ext/1810352431/usb_descriptors.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1810352431/usb_descriptors.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1056981605/gamma.p1: C:/Users/cpresser/_Daten/mplab_workspace/20_KarateLight/karate_xc8.X/src/gamma.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1056981605 
	@${RM} ${OBJECTDIR}/_ext/1056981605/gamma.p1.d 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G --asmlist  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug,9 --addrqual=require --mode=pro -P -N255 -I"src" -I"../../../../../../Program Files (x86)/Microchip/xc8/v1.34/include" --warn=0 --summary=default,-psect,-class,+mem,-hex,-file --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,-download,-stackcall,+config,+clib,+plib "--errformat=%%f:%%l: error: %%s" "--warnformat=%%f:%%l: warning: %%s" "--msgformat=%%f:%%l: advisory: %%s"  -o${OBJECTDIR}/_ext/1056981605/gamma.p1  C:/Users/cpresser/_Daten/mplab_workspace/20_KarateLight/karate_xc8.X/src/gamma.c 
	@-${MV} ${OBJECTDIR}/_ext/1056981605/gamma.d ${OBJECTDIR}/_ext/1056981605/gamma.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1056981605/gamma.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1056981605/karate.p1: C:/Users/cpresser/_Daten/mplab_workspace/20_KarateLight/karate_xc8.X/src/karate.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1056981605 
	@${RM} ${OBJECTDIR}/_ext/1056981605/karate.p1.d 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G --asmlist  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug,9 --addrqual=require --mode=pro -P -N255 -I"src" -I"../../../../../../Program Files (x86)/Microchip/xc8/v1.34/include" --warn=0 --summary=default,-psect,-class,+mem,-hex,-file --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,-download,-stackcall,+config,+clib,+plib "--errformat=%%f:%%l: error: %%s" "--warnformat=%%f:%%l: warning: %%s" "--msgformat=%%f:%%l: advisory: %%s"  -o${OBJECTDIR}/_ext/1056981605/karate.p1  C:/Users/cpresser/_Daten/mplab_workspace/20_KarateLight/karate_xc8.X/src/karate.c 
	@-${MV} ${OBJECTDIR}/_ext/1056981605/karate.d ${OBJECTDIR}/_ext/1056981605/karate.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1056981605/karate.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1056981605/tlc5947.p1: C:/Users/cpresser/_Daten/mplab_workspace/20_KarateLight/karate_xc8.X/src/tlc5947.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1056981605 
	@${RM} ${OBJECTDIR}/_ext/1056981605/tlc5947.p1.d 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G --asmlist  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug,9 --addrqual=require --mode=pro -P -N255 -I"src" -I"../../../../../../Program Files (x86)/Microchip/xc8/v1.34/include" --warn=0 --summary=default,-psect,-class,+mem,-hex,-file --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,-download,-stackcall,+config,+clib,+plib "--errformat=%%f:%%l: error: %%s" "--warnformat=%%f:%%l: warning: %%s" "--msgformat=%%f:%%l: advisory: %%s"  -o${OBJECTDIR}/_ext/1056981605/tlc5947.p1  C:/Users/cpresser/_Daten/mplab_workspace/20_KarateLight/karate_xc8.X/src/tlc5947.c 
	@-${MV} ${OBJECTDIR}/_ext/1056981605/tlc5947.d ${OBJECTDIR}/_ext/1056981605/tlc5947.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1056981605/tlc5947.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1056981605/configbits.p1: C:/Users/cpresser/_Daten/mplab_workspace/20_KarateLight/karate_xc8.X/src/configbits.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1056981605 
	@${RM} ${OBJECTDIR}/_ext/1056981605/configbits.p1.d 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G --asmlist  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug,9 --addrqual=require --mode=pro -P -N255 -I"src" -I"../../../../../../Program Files (x86)/Microchip/xc8/v1.34/include" --warn=0 --summary=default,-psect,-class,+mem,-hex,-file --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,-download,-stackcall,+config,+clib,+plib "--errformat=%%f:%%l: error: %%s" "--warnformat=%%f:%%l: warning: %%s" "--msgformat=%%f:%%l: advisory: %%s"  -o${OBJECTDIR}/_ext/1056981605/configbits.p1  C:/Users/cpresser/_Daten/mplab_workspace/20_KarateLight/karate_xc8.X/src/configbits.c 
	@-${MV} ${OBJECTDIR}/_ext/1056981605/configbits.d ${OBJECTDIR}/_ext/1056981605/configbits.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1056981605/configbits.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1056981605/comm.p1: C:/Users/cpresser/_Daten/mplab_workspace/20_KarateLight/karate_xc8.X/src/comm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1056981605 
	@${RM} ${OBJECTDIR}/_ext/1056981605/comm.p1.d 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G --asmlist  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug,9 --addrqual=require --mode=pro -P -N255 -I"src" -I"../../../../../../Program Files (x86)/Microchip/xc8/v1.34/include" --warn=0 --summary=default,-psect,-class,+mem,-hex,-file --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,-download,-stackcall,+config,+clib,+plib "--errformat=%%f:%%l: error: %%s" "--warnformat=%%f:%%l: warning: %%s" "--msgformat=%%f:%%l: advisory: %%s"  -o${OBJECTDIR}/_ext/1056981605/comm.p1  C:/Users/cpresser/_Daten/mplab_workspace/20_KarateLight/karate_xc8.X/src/comm.c 
	@-${MV} ${OBJECTDIR}/_ext/1056981605/comm.d ${OBJECTDIR}/_ext/1056981605/comm.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1056981605/comm.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1056981605/usb_hal_fixes.p1: C:/Users/cpresser/_Daten/mplab_workspace/20_KarateLight/karate_xc8.X/src/usb_hal_fixes.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1056981605 
	@${RM} ${OBJECTDIR}/_ext/1056981605/usb_hal_fixes.p1.d 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G --asmlist  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug,9 --addrqual=require --mode=pro -P -N255 -I"src" -I"../../../../../../Program Files (x86)/Microchip/xc8/v1.34/include" --warn=0 --summary=default,-psect,-class,+mem,-hex,-file --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,-download,-stackcall,+config,+clib,+plib "--errformat=%%f:%%l: error: %%s" "--warnformat=%%f:%%l: warning: %%s" "--msgformat=%%f:%%l: advisory: %%s"  -o${OBJECTDIR}/_ext/1056981605/usb_hal_fixes.p1  C:/Users/cpresser/_Daten/mplab_workspace/20_KarateLight/karate_xc8.X/src/usb_hal_fixes.c 
	@-${MV} ${OBJECTDIR}/_ext/1056981605/usb_hal_fixes.d ${OBJECTDIR}/_ext/1056981605/usb_hal_fixes.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1056981605/usb_hal_fixes.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/karate_xc8.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) --chip=$(MP_PROCESSOR_OPTION) -G --asmlist -mdist/${CND_CONF}/${IMAGE_TYPE}/karate_xc8.X.${IMAGE_TYPE}.map  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug,9 --addrqual=require --mode=pro -P -N255 -I"src" -I"../../../../../../Program Files (x86)/Microchip/xc8/v1.34/include" --warn=0 --summary=default,-psect,-class,+mem,-hex,-file --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,-download,-stackcall,+config,+clib,+plib "--errformat=%%f:%%l: error: %%s" "--warnformat=%%f:%%l: warning: %%s" "--msgformat=%%f:%%l: advisory: %%s"   -odist/${CND_CONF}/${IMAGE_TYPE}/karate_xc8.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	@${RM} dist/${CND_CONF}/${IMAGE_TYPE}/karate_xc8.X.${IMAGE_TYPE}.hex 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/karate_xc8.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) --chip=$(MP_PROCESSOR_OPTION) -G --asmlist -mdist/${CND_CONF}/${IMAGE_TYPE}/karate_xc8.X.${IMAGE_TYPE}.map  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,-asmfile,+speed,-space,-debug,9 --addrqual=require --mode=pro -P -N255 -I"src" -I"../../../../../../Program Files (x86)/Microchip/xc8/v1.34/include" --warn=0 --summary=default,-psect,-class,+mem,-hex,-file --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,-download,-stackcall,+config,+clib,+plib "--errformat=%%f:%%l: error: %%s" "--warnformat=%%f:%%l: warning: %%s" "--msgformat=%%f:%%l: advisory: %%s"   -odist/${CND_CONF}/${IMAGE_TYPE}/karate_xc8.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/18F45k20
	${RM} -r dist/18F45k20

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
