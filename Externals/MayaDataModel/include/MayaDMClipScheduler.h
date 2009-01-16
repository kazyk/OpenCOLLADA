/*
    Copyright (c) 2008 NetAllied Systems GmbH

    This file is part of MayaDataModel.

    Licensed under the MIT Open Source License,
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/
#ifndef __MayaDM_CLIPSCHEDULER_H__
#define __MayaDM_CLIPSCHEDULER_H__
#include "MayaDMTypes.h"
#include "MayaDMConnectables.h"
#include "MayaDMDependNode.h"
namespace MayaDM
{
class ClipScheduler : public DependNode
{
public:
	struct BlendList{
		struct BlendList_Inmap{
			short blendList_InmapTo;
			short blendList_InmapFrom;
			void write(FILE* file) const
			{
				fprintf(file,"%i ", blendList_InmapTo);
				fprintf(file,"%i", blendList_InmapFrom);
			}
		}* blendList_Inmap;
		struct BlendList_Outmap{
			short blendList_OutmapTo;
			short blendList_OutmapFrom;
			void write(FILE* file) const
			{
				fprintf(file,"%i ", blendList_OutmapTo);
				fprintf(file,"%i", blendList_OutmapFrom);
			}
		}* blendList_Outmap;
		void write(FILE* file) const
		{
			size_t size = sizeof(blendList_Inmap)/sizeof(BlendList_Inmap);
			for(size_t i=0; i<size; ++i)
			{
				blendList_Inmap[i].write(file);
				fprintf(file, " ");
				if(i+1<size) fprintf(file," ");
			}
			size = sizeof(blendList_Outmap)/sizeof(BlendList_Outmap);
			for(size_t i=0; i<size; ++i)
			{
				blendList_Outmap[i].write(file);
				if(i+1<size) fprintf(file," ");
			}
		}
	};
	struct BlendClips{
		int firstClip;
		int secondClip;
		void write(FILE* file) const
		{
			fprintf(file,"%i ", firstClip);
			fprintf(file,"%i", secondClip);
		}
	};
	struct ClipFunction{
		struct ClipFunction_Inmap{
			short clipFunction_InmapTo;
			short clipFunction_InmapFrom;
			void write(FILE* file) const
			{
				fprintf(file,"%i ", clipFunction_InmapTo);
				fprintf(file,"%i", clipFunction_InmapFrom);
			}
		}* clipFunction_Inmap;
		struct ClipFunction_Outmap{
			short clipFunction_OutmapTo;
			short clipFunction_OutmapFrom;
			void write(FILE* file) const
			{
				fprintf(file,"%i ", clipFunction_OutmapTo);
				fprintf(file,"%i", clipFunction_OutmapFrom);
			}
		}* clipFunction_Outmap;
		void write(FILE* file) const
		{
			size_t size = sizeof(clipFunction_Inmap)/sizeof(ClipFunction_Inmap);
			for(size_t i=0; i<size; ++i)
			{
				clipFunction_Inmap[i].write(file);
				fprintf(file, " ");
				if(i+1<size) fprintf(file," ");
			}
			size = sizeof(clipFunction_Outmap)/sizeof(ClipFunction_Outmap);
			for(size_t i=0; i<size; ++i)
			{
				clipFunction_Outmap[i].write(file);
				if(i+1<size) fprintf(file," ");
			}
		}
	};
public:
	ClipScheduler(FILE* file,const std::string& name,const std::string& parent=""):DependNode(file, name, parent, "clipScheduler"){}
	virtual ~ClipScheduler(){}
	void setBlendList(size_t bl_i,const BlendList& bl)
	{
		fprintf(mFile,"setAttr \".bl[%i]\" ",bl_i);
		bl.write(mFile);
		fprintf(mFile,";\n");

	}
	void setBlendList_Inmap(size_t bl_i,size_t bli_i,const BlendList::BlendList_Inmap& bli)
	{
		fprintf(mFile,"setAttr \".bl[%i].bli[%i]\" ",bl_i,bli_i);
		bli.write(mFile);
		fprintf(mFile,";\n");

	}
	void setBlendList_InmapTo(size_t bl_i,size_t bli_i,short blit)
	{
		if(blit == 0) return;
		fprintf(mFile,"setAttr \".bl[%i].bli[%i].blit\" %i;\n", bl_i,bli_i,blit);

	}
	void setBlendList_InmapFrom(size_t bl_i,size_t bli_i,short blif)
	{
		if(blif == 0) return;
		fprintf(mFile,"setAttr \".bl[%i].bli[%i].blif\" %i;\n", bl_i,bli_i,blif);

	}
	void setBlendList_Outmap(size_t bl_i,size_t blo_i,const BlendList::BlendList_Outmap& blo)
	{
		fprintf(mFile,"setAttr \".bl[%i].blo[%i]\" ",bl_i,blo_i);
		blo.write(mFile);
		fprintf(mFile,";\n");

	}
	void setBlendList_OutmapTo(size_t bl_i,size_t blo_i,short blot)
	{
		if(blot == 0) return;
		fprintf(mFile,"setAttr \".bl[%i].blo[%i].blot\" %i;\n", bl_i,blo_i,blot);

	}
	void setBlendList_OutmapFrom(size_t bl_i,size_t blo_i,short blof)
	{
		if(blof == 0) return;
		fprintf(mFile,"setAttr \".bl[%i].blo[%i].blof\" %i;\n", bl_i,blo_i,blof);

	}
	void setBlendClips(size_t bc_i,const BlendClips& bc)
	{
		fprintf(mFile,"setAttr \".bc[%i]\" ",bc_i);
		bc.write(mFile);
		fprintf(mFile,";\n");

	}
	void setFirstClip(size_t bc_i,int fcl)
	{
		if(fcl == 0) return;
		fprintf(mFile,"setAttr \".bc[%i].fcl\" %i;\n", bc_i,fcl);

	}
	void setSecondClip(size_t bc_i,int scl)
	{
		if(scl == 0) return;
		fprintf(mFile,"setAttr \".bc[%i].scl\" %i;\n", bc_i,scl);

	}
	void setClipFunction_Inmap(size_t cfi_i,const ClipFunction::ClipFunction_Inmap& cfi)
	{
		fprintf(mFile,"setAttr \".cf.cfi[%i]\" ",cfi_i);
		cfi.write(mFile);
		fprintf(mFile,";\n");

	}
	void setClipFunction_InmapTo(size_t cfi_i,short cfit)
	{
		if(cfit == 0) return;
		fprintf(mFile,"setAttr \".cf.cfi[%i].cfit\" %i;\n", cfi_i,cfit);

	}
	void setClipFunction_InmapFrom(size_t cfi_i,short cfif)
	{
		if(cfif == 0) return;
		fprintf(mFile,"setAttr \".cf.cfi[%i].cfif\" %i;\n", cfi_i,cfif);

	}
	void setClipFunction_Outmap(size_t cfo_i,const ClipFunction::ClipFunction_Outmap& cfo)
	{
		fprintf(mFile,"setAttr \".cf.cfo[%i]\" ",cfo_i);
		cfo.write(mFile);
		fprintf(mFile,";\n");

	}
	void setClipFunction_OutmapTo(size_t cfo_i,short cfot)
	{
		if(cfot == 0) return;
		fprintf(mFile,"setAttr \".cf.cfo[%i].cfot\" %i;\n", cfo_i,cfot);

	}
	void setClipFunction_OutmapFrom(size_t cfo_i,short cfof)
	{
		if(cfof == 0) return;
		fprintf(mFile,"setAttr \".cf.cfo[%i].cfof\" %i;\n", cfo_i,cfof);

	}
	void setScale(size_t sc_i,double sc)
	{
		if(sc == 1.0) return;
		fprintf(mFile,"setAttr \".sc[%i]\" %f;\n", sc_i,sc);

	}
	void setWeight(size_t w_i,double w)
	{
		if(w == 1.0) return;
		fprintf(mFile,"setAttr \".w[%i]\" %f;\n", w_i,w);

	}
	void setWeightStyle(size_t ws_i,unsigned int ws)
	{
		if(ws == 0) return;
		fprintf(mFile,"setAttr \".ws[%i]\" %i;\n", ws_i,ws);

	}
	void setPreCycle(size_t cb_i,double cb)
	{
		if(cb == 0.0) return;
		fprintf(mFile,"setAttr \".cb[%i]\" %f;\n", cb_i,cb);

	}
	void setPostCycle(size_t ca_i,double ca)
	{
		if(ca == 0.0) return;
		fprintf(mFile,"setAttr \".ca[%i]\" %f;\n", ca_i,ca);

	}
	void setEnable(size_t ea_i,bool ea)
	{
		if(ea == 1) return;
		fprintf(mFile,"setAttr \".ea[%i]\" %i;\n", ea_i,ea);

	}
	void setTrack(size_t tr_i,short tr)
	{
		if(tr == 0) return;
		fprintf(mFile,"setAttr \".tr[%i]\" %i;\n", tr_i,tr);

	}
	void setTrackState(size_t ts_i,short ts)
	{
		if(ts == 0) return;
		fprintf(mFile,"setAttr \".ts[%i]\" %i;\n", ts_i,ts);

	}
	void setNumTracks(short nt)
	{
		if(nt == 0) return;
		fprintf(mFile,"setAttr \".nt\" %i;\n", nt);

	}
	void setCycle(size_t cy_i,double cy)
	{
		if(cy == 1.0) return;
		fprintf(mFile,"setAttr \".cy[%i]\" %f;\n", cy_i,cy);

	}
	void getBlendList(size_t bl_i)
	{
		fprintf(mFile,"\"%s.bl[%i]\"",mName.c_str(),bl_i);

	}
	void getBlendList_Raw(size_t bl_i)
	{
		fprintf(mFile,"\"%s.bl[%i].blr\"",mName.c_str(),bl_i);

	}
	void getBlendList_Inmap(size_t bl_i,size_t bli_i)
	{
		fprintf(mFile,"\"%s.bl[%i].bli[%i]\"",mName.c_str(),bl_i,bli_i);

	}
	void getBlendList_InmapTo(size_t bl_i,size_t bli_i)
	{
		fprintf(mFile,"\"%s.bl[%i].bli[%i].blit\"",mName.c_str(),bl_i,bli_i);

	}
	void getBlendList_InmapFrom(size_t bl_i,size_t bli_i)
	{
		fprintf(mFile,"\"%s.bl[%i].bli[%i].blif\"",mName.c_str(),bl_i,bli_i);

	}
	void getBlendList_Outmap(size_t bl_i,size_t blo_i)
	{
		fprintf(mFile,"\"%s.bl[%i].blo[%i]\"",mName.c_str(),bl_i,blo_i);

	}
	void getBlendList_OutmapTo(size_t bl_i,size_t blo_i)
	{
		fprintf(mFile,"\"%s.bl[%i].blo[%i].blot\"",mName.c_str(),bl_i,blo_i);

	}
	void getBlendList_OutmapFrom(size_t bl_i,size_t blo_i)
	{
		fprintf(mFile,"\"%s.bl[%i].blo[%i].blof\"",mName.c_str(),bl_i,blo_i);

	}
	void getClipEvaluate()
	{
		fprintf(mFile,"\"%s.ce\"",mName.c_str());

	}
	void getClipFunction()
	{
		fprintf(mFile,"\"%s.cf\"",mName.c_str());

	}
	void getClipFunction_Raw()
	{
		fprintf(mFile,"\"%s.cf.cfr\"",mName.c_str());

	}
	void getClipFunction_Inmap(size_t cfi_i)
	{
		fprintf(mFile,"\"%s.cf.cfi[%i]\"",mName.c_str(),cfi_i);

	}
	void getClipFunction_InmapTo(size_t cfi_i)
	{
		fprintf(mFile,"\"%s.cf.cfi[%i].cfit\"",mName.c_str(),cfi_i);

	}
	void getClipFunction_InmapFrom(size_t cfi_i)
	{
		fprintf(mFile,"\"%s.cf.cfi[%i].cfif\"",mName.c_str(),cfi_i);

	}
	void getClipFunction_Outmap(size_t cfo_i)
	{
		fprintf(mFile,"\"%s.cf.cfo[%i]\"",mName.c_str(),cfo_i);

	}
	void getClipFunction_OutmapTo(size_t cfo_i)
	{
		fprintf(mFile,"\"%s.cf.cfo[%i].cfot\"",mName.c_str(),cfo_i);

	}
	void getClipFunction_OutmapFrom(size_t cfo_i)
	{
		fprintf(mFile,"\"%s.cf.cfo[%i].cfof\"",mName.c_str(),cfo_i);

	}
	void getClip(size_t cl_i)
	{
		fprintf(mFile,"\"%s.cl[%i]\"",mName.c_str(),cl_i);

	}
	void getStart(size_t st_i)
	{
		fprintf(mFile,"\"%s.st[%i]\"",mName.c_str(),st_i);

	}
	void getSourceStart(size_t ss_i)
	{
		fprintf(mFile,"\"%s.ss[%i]\"",mName.c_str(),ss_i);

	}
	void getSourceEnd(size_t se_i)
	{
		fprintf(mFile,"\"%s.se[%i]\"",mName.c_str(),se_i);

	}
	void getScale(size_t sc_i)
	{
		fprintf(mFile,"\"%s.sc[%i]\"",mName.c_str(),sc_i);

	}
	void getHold(size_t h_i)
	{
		fprintf(mFile,"\"%s.h[%i]\"",mName.c_str(),h_i);

	}
	void getWeight(size_t w_i)
	{
		fprintf(mFile,"\"%s.w[%i]\"",mName.c_str(),w_i);

	}
	void getWeightStyle(size_t ws_i)
	{
		fprintf(mFile,"\"%s.ws[%i]\"",mName.c_str(),ws_i);

	}
	void getPreCycle(size_t cb_i)
	{
		fprintf(mFile,"\"%s.cb[%i]\"",mName.c_str(),cb_i);

	}
	void getPostCycle(size_t ca_i)
	{
		fprintf(mFile,"\"%s.ca[%i]\"",mName.c_str(),ca_i);

	}
	void getEnable(size_t ea_i)
	{
		fprintf(mFile,"\"%s.ea[%i]\"",mName.c_str(),ea_i);

	}
	void getCycle(size_t cy_i)
	{
		fprintf(mFile,"\"%s.cy[%i]\"",mName.c_str(),cy_i);

	}
	void getStartPercent(size_t sp_i)
	{
		fprintf(mFile,"\"%s.sp[%i]\"",mName.c_str(),sp_i);

	}
	void getAbsolute(size_t a_i)
	{
		fprintf(mFile,"\"%s.a[%i]\"",mName.c_str(),a_i);

	}
	void getAbsoluteRotations(size_t ar_i)
	{
		fprintf(mFile,"\"%s.ar[%i]\"",mName.c_str(),ar_i);

	}
protected:
	ClipScheduler(FILE* file,const std::string& name,const std::string& parent,const std::string& nodeType):DependNode(file, name, parent, nodeType) {}

};
}//namespace MayaDM
#endif//__MayaDM_CLIPSCHEDULER_H__