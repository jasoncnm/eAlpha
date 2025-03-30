#if !defined(CAMERA_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Junjie Mao $
   $Notice: $
   ======================================================================== */

#include <glm/glm.hpp>

namespace Engine
{
    class OrthographicCamera
    {
    public:

        OrthographicCamera(r32 left, r32 right, r32 bottom, r32 top);

        void SetPosition(const glm::vec3 & position);    
        void SetRotation(r32 rotation);
        
        const glm::vec3 & GetPosition() const { return position; }
        const r32 GetRotation() const { return rotation; }

        const glm::mat4 & GetProjectionMatrix() const { return proj; }
        const glm::mat4 & GetViewMatrix() const { return view; }
        const glm::mat4 & GetVPMatrix() const { return viewProj; }
        
    private:

        void RecalculateViewMatrix();
        
        glm::mat4 proj;
        glm::mat4 view;
        glm::mat4 viewProj;

        glm::vec3 position = glm::vec3(0.0f);
        r32 rotation = 0.0f;
    };
}

#define CAMERA_H
#endif
