#pragma once

// uncomment and modify defines under for customize ImGuiFileDialog

// uncomment if you need to use your FileSystem Interface
// if commented, you have two defualt interface, std::filesystem or dirent
// #define USE_CUSTOM_FILESYSTEM

// this options need c++17
#define USE_STD_FILESYSTEM

//#define MAX_FILE_DIALOG_NAME_BUFFER 1024
//#define MAX_PATH_BUFFER_SIZE 1024

// the slash's buttons in path cna be used for quick select parallles directories
//#define USE_QUICK_PATH_SELECT

// the spacing between button path's can be customized. 
// if disabled the spacing is defined by the imgui theme
// define the space between path buttons 
//#define CUSTOM_PATH_SPACING 2

// #define USE_THUMBNAILS
//the thumbnail generation use the stb_image and stb_resize lib who need to define the implementation
//btw if you already use them in your app, you can have compiler error due to "implemntation found in double"
//so uncomment these line for prevent the creation of implementation of these libs again
// #define DONT_DEFINE_AGAIN__STB_IMAGE_IMPLEMENTATION
// #define DONT_DEFINE_AGAIN__STB_IMAGE_RESIZE_IMPLEMENTATION
// #define IMGUI_RADIO_BUTTON RadioButton
// #define DisplayMode_ThumbailsList_ImageHeight 32.0f
// #define tableHeaderFileThumbnailsString "Thumbnails"
// #define DisplayMode_FilesList_ButtonString "FL"
// #define DisplayMode_FilesList_ButtonHelp "File List"
// #define DisplayMode_ThumbailsList_ButtonString "TL"
// #define DisplayMode_ThumbailsList_ButtonHelp "Thumbnails List"
// todo
//#define DisplayMode_ThumbailsGrid_ButtonString "TG"
//#define DisplayMode_ThumbailsGrid_ButtonHelp "Thumbnails Grid"

//#define USE_EXPLORATION_BY_KEYS
// this mapping by default is for GLFW but you can use another
//#include <GLFW/glfw3.h> 
// Up key for explore to the top
//#define IGFD_KEY_UP ImGuiKey_UpArrow
// Down key for explore to the bottom
//#define IGFD_KEY_DOWN ImGuiKey_DownArrow
// Enter key for open directory
//#define IGFD_KEY_ENTER ImGuiKey_Enter
// BackSpace for comming back to the last directory
//#define IGFD_KEY_BACKSPACE ImGuiKey_Backspace

// by ex you can quit the dialog by pressing the key excape
//#define USE_DIALOG_EXIT_WITH_KEY
//#define IGFD_EXIT_KEY ImGuiKey_Escape

// widget
// begin combo widget
//#define IMGUI_BEGIN_COMBO ImGui::BeginCombo
// when auto resized, FILTER_COMBO_MIN_WIDTH will be considered has minimum width
// FILTER_COMBO_AUTO_SIZE is enabled by default now to 1
// uncomment if you want disable
//#define FILTER_COMBO_AUTO_SIZE 0
// filter combobox width
//#define FILTER_COMBO_MIN_WIDTH 120.0f
// button widget use for compose path
//#define IMGUI_PATH_BUTTON ImGui::Button
// standard button
//#define IMGUI_BUTTON ImGui::Button

// locales string
//#define createDirButtonString "+"
//#define resetButtonString "R"
//#define drivesButtonString "Drives"
//#define editPathButtonString "E"
//#define searchString "Search"
//#define dirEntryString "[DIR] "
//#define linkEntryString "[LINK] "
//#define fileEntryString "[FILE] "
//#define fileNameString "File Name : "
//#define dirNameString "Directory Path :"
//#define buttonResetSearchString "Reset search"
//#define buttonDriveString "Drives"
//#define buttonEditPathString "Edit path\nYou can also right click on path buttons"
//#define buttonResetPathString "Reset to current directory"
//#define buttonCreateDirString "Create Directory"
//#define OverWriteDialogTitleString "The file Already Exist !"
//#define OverWriteDialogMessageString "Would you like to OverWrite it ?"
//#define OverWriteDialogConfirmButtonString "Confirm"
//#define OverWriteDialogCancelButtonString "Cancel"

//Validation buttons
//#define okButtonString " OK"
//#define okButtonWidth 0.0f
//#define cancelButtonString " Cancel"
//#define cancelButtonWidth 0.0f
//alignement [0:1], 0.0 is left, 0.5 middle, 1.0 right, and other ratios
//#define okCancelButtonAlignement 0.0f
//#define invertOkAndCancelButtons 0

// DateTimeFormat
// see strftime functionin <ctime> for customize
// "%Y/%m/%d %H:%M" give 2021:01:22 11:47
// "%Y/%m/%d %i:%M%p" give 2021:01:22 11:45PM
//#define DateTimeFormat "%Y/%m/%d %i:%M%p"

// theses icons will appear in table headers
//#define USE_CUSTOM_SORTING_ICON
//#define tableHeaderAscendingIcon "A|"
//#define tableHeaderDescendingIcon "D|"
//#define tableHeaderFileNameString " File name"
//#define tableHeaderFileTypeString " Type"
//#define tableHeaderFileSizeString " Size"
//#define tableHeaderFileDateTimeString " Date"
//#define fileSizeBytes "o"
//#define fileSizeKiloBytes "Ko"
//#define fileSizeMegaBytes "Mo"
//#define fileSizeGigaBytes "Go"

// default table sort field (must be FIELD_FILENAME, FIELD_TYPE, FIELD_SIZE, FIELD_DATE or FIELD_THUMBNAILS)
//#define defaultSortField FIELD_FILENAME

// default table sort order for each field (true => Descending, false => Ascending)
//#define defaultSortOrderFilename true
//#define defaultSortOrderType true
//#define defaultSortOrderSize true
//#define defaultSortOrderDate true
//#define defaultSortOrderThumbnails true

//#define USE_BOOKMARK
//#define bookmarkPaneWith 150.0f
//#define IMGUI_TOGGLE_BUTTON ToggleButton
//#define bookmarksButtonString "Bookmark"
//#define bookmarksButtonHelpString "Bookmark"
//#define addBookmarkButtonString "+"
//#define removeBookmarkButtonString "-"

static const char IGFD_compressed_data_base85[3950+1] = 
    "7])#######Dl_0_'/###O@?>#+lQS%Ql#v#X^@iFm,6TH$&(##/i(##[[S=B7Rm.L:^Ee-]br-$KQshF=I&##'h$##<L]w',>p0FSQM:L3/Uw02)[w'o;<RDQjUw#IPH_&8Jq-$Mu@['"
    "@c9*NbUD_&UKo-$fZIkESHP_?Xq&##a+(##n9?0Fb$'3^>Z%F7Acg--&OMkOQ&###U::d?odPirc[4gL_=$##+Yk>3;IGF%:=1?%+$-tL]em##PPL@-#VGs-Vi[+M4:T/Lr.TV-vtXR*"
    "?=th#@fNX($W3&+5OOX(uue+MQxSfLaH<mL(x$m/mEexFTP'##>Uu)NuDOd$nGZ(%/@$Z$3.5F%>Lqk+GN=_/)@v;%V8C5M$@,gL1F5gL$@,gLKoG8.'5>##<F`p&C./YcZwKv-$;d'&"
    "?dd.qjm$0qT4Q3qA^:7q'>b9qObm;qn&nCq,R[SqOim4vn/-F.PjoF.m7VQIB5KG.?(5k#iYkr-EX:p/'cYS.$-_'#RAB;-d+$L-Swxe%P]UV$0u68%47no%8ONP&<h/2'@*gi'DBGJ("
    "HZ(,)Ls_c).fP7ERrD_&Q7)##pU(##Djo-$:H+##F&'##S:m-$O=)##@Sl-$7J(##)ak-$WQo-$&U79&G(35&?).m/:3NP&r:jl&<?u`3eE/2'hNJM'jLJM'na+/(9/5##9:m`-kj/I$"
    "n&&)#Xn@X-jbtM(pSLnuw);GV_u.Dt?ba@tEfJ&#QTV'#T%J/LZ:;8%rtJfLXu5;-Su4;-bkh8.E7TfL7.SY.n,Ih(Lv_>$u7XI)E$X=$FR]tuVbxX#KF-,$6+hF4Ns5c]5]4xt(l0o`"
    "HG]Y,V=SqFs-*#/>BxY-2>6=1SS@n3BQQY>tQZ50K;6xtBE3muOYE6j1#'58SM?o'r)#,2]V5D<G.H]F2[ZuP%2G>#kTSf-S9w0#k5e4vgYq3vH+6AM3(.m//tTB#6k9'#l1^gLT,pY-"
    "->pH7TGl0-lfn0-m:-nkQjR)vt=X4'FK5.8hjkA#.2T>-T5T>-.Z)/V6*;Ga,n8f0)5###u/f##@P+58FT`>nhvYK7x(f+MfN#Vd:E`48:P$$$bl9'#])UK*O*oMMqAh1TdFi(EPpkr7"
    "Hp`Js$T-##[YEt$bcx5#->Ha2F(@8%&Y@C#i_Z=7No^I*7nJ,2&f^DNGM1eN47DcNF<w%,(o'B#`//;MJ)Nfq57x:.3.v(EL.o&,pRpq#:a^)4=_)AF)bBg(2o58.[[5K)[(Ls-/t/I$"
    "OEU*@hPt>P(&cI)9r_V$6^`A.,k`Cjj&nA#Y7,HM+@75/8e9:)K4j'MdZwe-fcBN,g6'@9<5jD3YdUV$sRk&#l,>>#@D5##]o;T/,oK9/)$fF4k&B.*-7T^,k(TF4^.RM0Rq@.*bZ'u$"
    "cJF/M;`6<.*M4gL;ngo0TAOZ6W.PV-RVx_4QmuX$KOj`ub>(6RTcZULbR39/oBfU+-p9x9SP>bnQ5&X%pbO-)&-g[us_.u-=^7>N8$EG'i_7MTv+qM#ReBtLg@RxktpqbrUv?rC*+8C8"
    "i&X1)e61nLx-$O*%@h-Ml=DX-xv@=(`()?#B8WeFW-u?-vOlo.$&>uuu]iQjhx###6T&],vQnW_$Dh8.w-<?#PE3j1j.dx3stb@$RieX-PbU/)9,d]u*l0[.p2rE3*cA/L>%jx-q-U&5"
    "YZbA#Dc$a-1F-Z$3(m<-2&&b-cjHwB)j9e$*fF.#=F.%#bWt&#M3>V/2T/i)HrUv-F^?d))2pb4N*sKG'L/@#H`G>#x]5.3Z_[@#1N.Q@2eV5*k+)ul=^hA4+;wA4-l2%bt_NPoN%g1B"
    "Yb]+42bMjLXF8:La,3.M58+**]kp)4JP`,u2U`k#Z-qDX;BgF/['9'#/W%RNV]UV$l(+&#g9e5/l)qH*c4oL(u3YD#=@)ns>4vr-Fdsw$/_?C+ohAYcqT@E+iW0KMes=p%%<TB+eq]o&"
    "x$1v%Y_L=M/ifbMat0AXt&q`MYid##kJ,/19mb;-1u$+5&b+X$xIkI)ig'u$ikkj1./.&4maJX-Wh3a%BNg@#<:%[u;C]:/F^BBTXTi>.MvUk'R3Tm&?`I34s'o7l=E^[#JN$q3JDDW-"
    "ex,##/snC>+[Ch4DZVs%am^q%hh)?#51&>Nd:1##aJ^'/YdYEnVKpdm$7[0#G,>>#b1=Z-)7(dMjCCv-gc``36SqcNKQL,3L1O058b4-5mS4'5841'5%J/GV/1:B#'at%$q^DIM=X0DM"
    "3)^fL6)0/Ldbb(NRdimM-a4o7qPa>$cMDX:W<=&5R^i'#C.0u$CGF&#]rgo.NV9h&h0`.3f`aI)wuj=)V_TLpB9o*%j70.)@*4F%C6pre.3^gL8u+.)$Ja1)1K2.)/us'4`1iv?[x[AX"
    ">DQk=&2SfL>4-m'3HBMu2:nmL3Bi-McE;,)odGb@L.N'MU@9C-]?KoLDulhL#w5D-#TVA./JE/Lq>eA#/'+Q8l]9C,8&B.*5XKb@@hsPM2.VfLFI8GVRmDGV+:2X-*<dq)mAn9M3>6##"
    "#+d;%$9P-4avK'#?3B:%V::8.mNv)4#Vpr6xXl<:-%eX-Si(?#LR(*>=:mp1J4@]u2NVE87mV)4lKxnLI_lS7#e$YYd>h>fjqBj$S>1T2&idh#WNc]u,VoH+/^(B#dS3N0_HDbA:lD)%"
    "rNHAOYMYGMDtJfLXqd##Q3=&#d72mLvG(u$+dfF4<BPF%MPEb3:]Me.d(4I)(P;e.)_K#$^n;#MjXGp%jDJeM20P.)'9_-2[x):8,VjfLQJa0V*#4o7dD24'^bO-)GX3/U@@%P'9/8b*"
    ";XmGA9Gw;8i=I`(sZhM'8A]?cof-6M>Awx-tS<GMRoS+MWWB@#WG9J'P@)?uNUYI8#-EE#[Yw_#;R,<8+b?:3LljD3Yr@/LGVOV-D'%29M#_B#4ZCD3S)&T/29orNwJ1N(e]YD4Oea,*"
    "-4h0,>4vr-4Hc#6<-C]$N>.U%))^Y,SEW-$$;(v#B%C7&D$KH2;YvAupvh4L]/8$$n=x_uGM1-Mh?^;-0@;=->?DiL9El'0dWe`*>(t.L&A3/LnQE?#HnMR8HeFatBUj'0i%s^#X-L4."
    "mV-6M3:#gL=E5',2F_oA&>uu#R%=cMEjV&#[S@^$Ki@@-s3emLjnU6v0w)-vjKJ_MYF$##iBBY$@Y6iL*JqY-M=#/?'.^.?\?@i%aI%'0%KGY##CoRe*5nOJ(h5.)*jr/+*dg0aYctH##"
    "6^TlS;4T=YPuG;-K6^/N4i`>$agNe'Qk[X'ep.'5ab5'5uX(T73OWV$Pi[+MT([##PG<A+q^EM0Ue$##`q-q$V2Cv-b%w20tt?X-BL75/#(KU)N0;hLr75c4br9s-;va.3exLG`^U;4F"
    "RcG$0%IFL#[/;Zu[$^iB841'5Po7/Lb2=CLIw[%=En$SV8J$1,(dWIL=#gr/agM%O1Q;>5@R<=$/rVB#kwF>#euita$X82LhuA&GBihNXcIIa4u<'8@Pc&6/-@XA#R4r?#fgGj'x%MT/"
    "ObE]-QtfM'-Wgf16HSP/kK(E#_3rhLE)t1)ter0,7D?whd]g^%11uU&FIJa^d/Gb%QIsYlG4`;$]Ya7Q.sc7Iw<6AO2CL97I)Ta#?u//LEJS8/^wJ/rD,?V%O)8'.<aMhLmME.h>x4Au"
    "%<dD-$EmD-.]GW-sROwBG/5##iGIg:;,>>#*AY>#.Ml>#2Y(?#6f:?#:rL?#>(`?#B4r?#F@.@#JL@@#NXR@#W<Bu$%QcdGjr_hCi'-[Av)/:C*oIbHnQ`=BG)boM0$%oDT#0V)uMX]F"
    "YNM<Br,9kEix@qC,dKSDm*;iF%jcdG]p[9C+1#wGxT;]A8X0DIaZ=b$cf3PCaT79CfxBVC1#lVC_S@UC?SvLFu@jx&D$L3C)Z_(%u2J:C6sXdM)6RgFn#_(%/xn'ItR/vGj;_$&SEb3O"
    ")Bl'&3,R['3pitBlq>LF9n8AtHKCw/";

#define FONT_ICON_BUFFER_NAME_IGFD IGFD_compressed_data_base85

#define FONT_ICON_BUFFER_SIZE_IGFD 0xf6e

#define ICON_MIN_IGFD 0xf002
#define ICON_MAX_IGFD 0xf1c9

#define ICON_IGFD_ADD u8"\uf067"
#define ICON_IGFD_BOOKMARK u8"\uf02e"
#define ICON_IGFD_CANCEL u8"\uf00d"
#define ICON_IGFD_CHEVRON_DOWN u8"\uf078"
#define ICON_IGFD_CHEVRON_UP u8"\uf077"
#define ICON_IGFD_DRIVES u8"\uf0a0"
#define ICON_IGFD_EDIT u8"\uf040"
#define ICON_IGFD_FILE u8"\uf15b"
#define ICON_IGFD_FILE_GRID_THUMBNAILS u8"\uf00a"
#define ICON_IGFD_FILE_LIST u8"\uf0c9"
#define ICON_IGFD_FILE_LIST_THUMBNAILS u8"\uf00b"
#define ICON_IGFD_FILE_PIC u8"\uf1c5"
#define ICON_IGFD_FOLDER u8"\uf07b"
#define ICON_IGFD_FOLDER_OPEN u8"\uf07c"
#define ICON_IGFD_LINK u8"\uf1c9"
#define ICON_IGFD_OK u8"\uf00c"
#define ICON_IGFD_REFRESH u8"\uf021"
#define ICON_IGFD_REMOVE u8"\uf068"
#define ICON_IGFD_RESET u8"\uf064"
#define ICON_IGFD_SAVE u8"\uf0c7"
#define ICON_IGFD_SEARCH u8"\uf002"
#define ICON_IGFD_STEP_FORWARD u8"\uf051"