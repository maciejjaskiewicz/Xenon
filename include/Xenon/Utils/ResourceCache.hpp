#pragma once

#include "ResourceLoader.hpp"

namespace Xenon
{
    template<typename TResource>
    class ResourceCache
    {
    public:
        template<typename TLoader, typename TArgs = ResourceLoaderArgs>
        void set(const std::string& id, const TArgs& args)
        {
            static_assert(std::is_base_of_v<ResourceLoaderArgs, TArgs>);
            static_assert(std::is_base_of_v<ResourceLoader<TResource, TArgs>, TLoader>);

            XN_ASSERT_FMT(!contains(id), "Resource Cache already contains a resource with ID: {}", id);

            auto loader = new TLoader{};
            loader->mArgs = args;
            loader->mInitialized = true;

            ResourceEntry entry
            {
                std::shared_ptr<TResource>(),
                std::unique_ptr<IResourceLoader<TResource>>(static_cast<IResourceLoader<TResource>*>(loader))
            };

            mResources.emplace(id, std::move(entry));
        }

        template<typename TLoader, typename TArgs = ResourceLoaderArgs>
        std::shared_ptr<TResource> load(const std::string& id, const TArgs& args)
        {
            if (!contains(id))
            {
                set<TLoader, TArgs>(id, args);
            }

            return load(id);
        }

        std::shared_ptr<TResource> load(const std::string& id)
        {
            std::shared_ptr<TResource> resource;

            if (auto it = mResources.find(id); it != mResources.cend())
            {
                if (!it->second.resource)
                {
                    it->second.resource = it->second.loader->load();
                }

                resource = it->second.resource;
            }

            return resource;
        }

        template<typename TLoader, typename TArgs = ResourceLoaderArgs>
        std::shared_ptr<TResource> reload(const std::string& id, const TArgs& args)
        {
            free(id);
            return load<TLoader, TArgs>(id, args);
        }

        void free(const std::string& id)
        {
            if (auto it = mResources.find(id); it != mResources.end())
                mResources.erase(it);
        }

        [[nodiscard]] bool contains(const std::string& id) const
        {
            return (mResources.find(id) != mResources.cend());
        }

        [[nodiscard]] uint32_t count() const noexcept
        {
            return mResources.size();
        }

        [[nodiscard]] bool empty() const noexcept
        {
            return mResources.empty();
        }

        void clear() noexcept
        {
            mResources.clear();
        }

    private:
        struct ResourceEntry
        {
            std::shared_ptr<TResource> resource;
            std::unique_ptr<IResourceLoader<TResource>> loader;
        };

        std::unordered_map<std::string, ResourceEntry> mResources;
    };
}