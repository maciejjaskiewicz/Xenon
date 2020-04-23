#pragma once

#include "Xenon/Core/Api.hpp"

#include <memory>

namespace Xenon
{
    template<typename>
    class ResourceCache;

    struct ResourceLoaderArgs
    { };

    template<typename TResource>
    class IResourceLoader
    {
    public:
        virtual ~IResourceLoader() = default;

        XN_NODISCARD virtual std::shared_ptr<TResource> load() const = 0;
    };

    template<typename TResource, typename TArgs = ResourceLoaderArgs>
    class ResourceLoader : public IResourceLoader<TResource>
    {
    public:
        ResourceLoader() = default;
        explicit ResourceLoader(const TArgs& args)
            : mInitialized(true), mArgs(args)
        { }

        XN_NODISCARD const TArgs& getArgs() const
        {
            XN_ASSERT_COM(mInitialized, "Uninitialized resource loeader!");
            return mArgs;
        }

    private:
        bool mInitialized{};
        TArgs mArgs{};

        friend class ResourceCache<TResource>;
    };
}