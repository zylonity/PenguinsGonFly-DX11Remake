#include "ModeMgr.h"

void ModeMgr::SwitchMode(const std::string& newMode) {
	int idx = 0;
	assert(!mModes.empty());
	while (idx < (int)mModes.size() && mModes[idx]->GetMName() != newMode)
		++idx;
	assert(idx < (int)mModes.size());
	mDesiredMIdx = idx;
}

void ModeMgr::Update(float dTime, MyD3D& d3d) {
	if (mDesiredMIdx != mCurrentMIdx)
		if (mCurrentMIdx == -1 || mModes[mCurrentMIdx]->Exit())
		{
			mCurrentMIdx = mDesiredMIdx;
			mModes[mCurrentMIdx]->Enter();
		}
	assert(mCurrentMIdx >= 0 && mCurrentMIdx < mModes.size());
	mModes[mCurrentMIdx]->Update(dTime, d3d);
}

void ModeMgr::Render(float dTime, MyD3D& d3d) {
	if (mCurrentMIdx >= 0 && mCurrentMIdx < (int)mModes.size())
		mModes[mCurrentMIdx]->Render(dTime, d3d);
}

void ModeMgr::ProcessKey(char key) {
	if (mCurrentMIdx >= 0 && mCurrentMIdx < (int)mModes.size())
		mModes[mCurrentMIdx]->ProcessKey(key);
}

void ModeMgr::AddMode(AMode* p) {
	assert(p);
	mModes.push_back(p);
}

void ModeMgr::Release() {
	for (size_t i = 0; i < mModes.size(); ++i)
		delete mModes[i];
	mModes.clear();
}
