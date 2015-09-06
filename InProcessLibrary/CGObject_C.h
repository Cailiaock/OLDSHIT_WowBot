#pragma once

enum TypeID
{
    TYPEID_OBJECT           = 0,
    TYPEID_ITEM             = 1,
    TYPEID_CONTAINER        = 2,
    TYPEID_UNIT             = 3,
    TYPEID_PLAYER           = 4,
    TYPEID_GAMEOBJECT       = 5,
    TYPEID_DYNAMICOBJECT    = 6,
    TYPEID_CORPSE           = 7,
    NUM_TYPEIDS             = 8
};

struct C3Vector
{
    float X, Y, Z;
};

class CGObject_C // sizeof(CGObject_C) == 0xD0
{
public:
    template <typename T> T& GetValue(uint32 index) const { return *((T*)&m_data[index]); }

    virtual ~CGObject_C(); // 0
    virtual void Disable()=0; // 1
    virtual void Reenable()=0; // 2 Reenable(CClientObjCreate  const&)
    virtual void PostReenable()=0; // 3 PostReenable(CClientObjCreate  const&)
    virtual void HandleOutOfRange()=0; // 4 HandleOutOfRange(OUT_OF_RANGE_TYPE)
    virtual void UpdateWorldObject()=0; // 5 UpdateWorldObject(int)
    virtual void ShouldFadeout()=0; // 6
    virtual void UpdateDisplayInfo()=0; // 7 UpdateDisplayInfo(int)
    virtual void GetNamePosition()=0; // 8
    virtual void GetBag()=0; // 9
    virtual void GetBag2()=0; // 10
    virtual void FloatingTooltip()=0; // 11 GetPosition(C3Vector &)
    virtual C3Vector& GetRawPosition(C3Vector &pos)=0; // 12 GetRawPosition(C3Vector &)
    virtual float GetFacing()=0; // 13
    virtual float GetRawFacing()=0; // 14
    virtual float GetScale()=0; // 15
    virtual uint64 GetTransportGUID()=0; // 16
    virtual void GetRotation()=0; // 17 returns C4Quaternion
    virtual void SetFrameOfReference()=0; // 18 SetFrameOfReference(C44Matrix  const*)
    virtual BOOL IsQuestGiver()=0; // 19
    virtual void RefreshInteractIcon()=0; // 20
    virtual void UpdateInteractIcon()=0; // 21
    virtual void UpdateInteractIconAttach()=0; // 22
    virtual void UpdateInteractIconScale()=0; // 23
    virtual BOOL GetModelFileName(char const** modelFileName)=0; // 24 GetModelFileName(char  const**)
    virtual void ScaleChangeUpdate()=0; // 25
    virtual void ScaleChangeFinished()=0; // 26
    virtual void RenderTargetSelection()=0; // 27
    virtual void RenderPetTargetSelection()=0; // 28
    virtual void Render()=0; // 29
    virtual void GetSelectionHighlightColor()=0; // 30 GetSelectionHighlightColor(CImVector *)
    virtual float GetTrueScale()=0; // 31
    virtual void ModelLoaded()=0; // 32 ModelLoaded(CM2Model *)
    virtual void ApplyAlpha()=0; // 33 ApplyAlpha(uint)
    virtual void PreAnimate()=0; // 34 PreAnimate(CGWorldFrame *)
    virtual void Animate()=0; // 35 Animate(float)
    virtual void ShouldRender()=0; // 36 ShouldRender(uint,int &,int &)
    virtual float GetRenderFacing()=0; // 37
    virtual void OnSpecialMountAnim()=0; // 38
    virtual BOOL IsSolidSelectable()=0; // 39
    virtual void Dummy40()=0; // 40
    virtual BOOL CanHighlight()=0; // 41
    virtual BOOL CanBeTargetted()=0; // 42
    virtual C3Vector & GetPosition(C3Vector &pos)=0; // 43
    virtual void OnRightClick()=0; // 44
    virtual BOOL IsHighlightSuppressed()=0; // 45
    virtual void OnSpellEffectClear()=0; // 46 OnSpellEffectClear(CEffect *)
    virtual void GetAppropriateSpellVisual()=0; // 47 GetAppropriateSpellVisual(SpellRec  const*,SpellVisualRec &,int,int)
    virtual void ConnectToLightningThisFrame()=0; // 48 ConnectToLightningThisFrame(uint,int)
    virtual void GetMatrix()=0; // 49
    virtual void ObjectNameVisibilityChanged()=0; // 50 
    virtual void UpdateObjectNameString()=0; // 51 UpdateObjectNameString(int,char *,uint)
    virtual void ShouldRenderObjectName()=0; // 52 ShouldRenderObjectName(int)
    virtual void GetObjectModel()=0; // 53
    virtual void function54()=0;  // 54
    virtual void GetPageTextID()=0; // 55 GetPageTextID(void (*)(int,ulong long  const&,void *,bool))
    virtual void CleanUpVehicleBoneAnimsBeforeObjectModelChange()=0; // 56
    virtual void ShouldFadeIn()=0; // 57
    virtual float GetBaseAlpha()=0; // 58
    virtual BOOL IsTransport()=0; // 59
    virtual BOOL IsPointInside()=0; // 60 IsPointInside(C3Vector  const&)
    virtual void AddPassenger()=0; // 61 AddPassenger(CPassenger *,int)
    virtual float GetSpeed()=0; // 62
    virtual void PlaySpellVisualKit_PlayAnims()=0; // 63 PlaySpellVisualKit_PlayAnims(SpellRec  const*,SpellVisualKitRec  const*,SPELL_VISUAL_KIT_TYPE,C3Vector  const*,int,int,ulong long,ulong,SpellVisualRec  const*,uint,int)
    virtual void PlaySpellVisualKit_HandleWeapons()=0; // 64 PlaySpellVisualKit_HandleWeapons(SpellRec  const*,SpellVisualKitRec  const*,C3Vector  const*,ulong long,ulong,uint,void (*)(CM2Model *,uint,uint,int,uint,ulong long,int),int *,uint,int)
    virtual void PlaySpellVisualKit_DelayLightningEffects()=0; // 65 PlaySpellVisualKit_DelayLightningEffects(SpellRec  const*,SpellVisualKitRec  const*,SPELL_VISUAL_KIT_TYPE,C3Vector  const*,ulong long,int,int,int,int,uint,SpellVisualRec  const*,uint,int)
	virtual void function66()=0;
	virtual void function67()=0;
	virtual void function68()=0;
	virtual void function69()=0;
	virtual void function70()=0;
	virtual void function71()=0;
	virtual void function72()=0;
	virtual void function73()=0;
	virtual void function74()=0;
	virtual void function75()=0;
	virtual void function76()=0;
	virtual void function77()=0;
	virtual void function78()=0;
	virtual void function79()=0;
	virtual void function80()=0;
	virtual void function81()=0;
	virtual void function82()=0;
	virtual void function83()=0;
	virtual void function84()=0;
	virtual void function85()=0;
	virtual const char* GetObjectName()=0;
	/*
	virtual void function87()=0;
	virtual void function88()=0;
	virtual void function89()=0;
	virtual void function90()=0;
	virtual void function91()=0;
	virtual void function92()=0;
	virtual void function93()=0;
	virtual void function94()=0;
	virtual void function95()=0;
	virtual void function96()=0;
	virtual void function97()=0;
	virtual void function98()=0;
	virtual void function99()=0;
	virtual void function100()=0;
	virtual void function101()=0;
	virtual void function102()=0;
	virtual void function103()=0;
	virtual void function104()=0;
	*/
    //TypeID GetTypeID() const { return m_typeID; }
private:
    // void* vtable;        // 0x0
    uint32 m_field4;        // 0x4
    uint32 *m_data;         // 0x8
    char m_typeID;         // 0xC
    uint32 m_field10;       // 0x10
	uint32 m_field20[4];        //20
           // 0x14
    uint32 m_field18[46];   // 0x18



};
