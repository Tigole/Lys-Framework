#ifndef _A_HPP
#define _A_HPP 1

#include <lys-module-application-states.hpp>

class LayerA: public lys::ApplicationLayer
{
public:
    LayerA();

    void On_Activate(void) override;
    void On_Deactivate(void) override;

    lys::ApplicationLayerForward On_Update(void) override;
    void On_Render(void) override;
    lys::ApplicationLayerForward Get_Rendering_Forward_Strategy(void) const override;
};

class StateA: public lys::ApplicationState
{
public:
    StateA();

    void On_Create(void);
    void On_Destroy(void);

    void On_Entry(void);
    void On_Exit(void);

private:
    LayerA layerA;
};

#endif  // _A_HPP
