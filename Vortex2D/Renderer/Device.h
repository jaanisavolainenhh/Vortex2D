//
//  Device.h
//  Vortex2D
//

#ifndef Device_h
#define Device_h

#include <Vortex2D/Renderer/Common.h>

namespace Vortex2D { namespace Renderer {

class Device
{
public:
    Device(vk::PhysicalDevice physicalDevice, bool validation = true);
    Device(vk::PhysicalDevice physicalDevice, vk::SurfaceKHR surface, bool validation = true);
    Device(vk::PhysicalDevice physicalDevice, int familyIndex, bool validation = true);

    vk::Device Handle() const;
    vk::Queue Queue() const;
    vk::DescriptorPool DescriptorPool() const;
    vk::PhysicalDevice GetPhysicalDevice() const;
    std::vector<vk::CommandBuffer> CreateCommandBuffers(uint32_t size) const;
    void FreeCommandBuffers(vk::ArrayProxy<const vk::CommandBuffer> commandBuffers) const;

    // TODO replace with command buffer ring
    // TODO use barrier instead of fence
    template<typename F>
    void ExecuteCommand(F f)
    {
        vk::CommandBuffer cmd = CreateCommandBuffers(1).at(0);

        auto cmdBeginInfo = vk::CommandBufferBeginInfo()
                .setFlags(vk::CommandBufferUsageFlagBits::eOneTimeSubmit);

        cmd.begin(cmdBeginInfo);
        f(cmd);
        cmd.end();

        auto submitInfo = vk::SubmitInfo()
                .setCommandBufferCount(1)
                .setPCommandBuffers(&cmd);

        mQueue.submit({submitInfo}, nullptr);
        mQueue.waitIdle();
        FreeCommandBuffers({cmd});
    }

    uint32_t FindMemoryPropertiesIndex(uint32_t memoryTypeBits, vk::MemoryPropertyFlags properties) const;
    vk::DescriptorSetLayout CreateDescriptorSetLayout(vk::DescriptorSetLayoutCreateInfo layoutInfo) const;
    vk::ShaderModule CreateShaderModule(vk::ShaderModuleCreateInfo moduleInfo) const;

private:
    vk::PhysicalDevice mPhysicalDevice;
    vk::UniqueDevice mDevice;
    vk::Queue mQueue;
    vk::UniqueCommandPool mCommandPool;
    vk::UniqueDescriptorPool mDescriptorPool;
    mutable std::vector<vk::UniqueDescriptorSetLayout> mDescriptorSetLayouts;
    mutable std::vector<vk::UniqueShaderModule> mShaders;
};

}}

#endif