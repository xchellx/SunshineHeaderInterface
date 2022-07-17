#pragma once

#include <JSystem/JDrama/JDRViewConnector.hxx>

class TCamConnector : public JDrama::TViewConnector {
public:
    virtual ~TCamConnector();

    virtual void perform(u32, JDrama::TGraphics *);
};