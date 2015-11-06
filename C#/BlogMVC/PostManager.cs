using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using CapstoneBlog.Data;
using CapstoneBlog.Models;

namespace CapstoneBlog.BLL
{
    public class PostManager
    {
        PostRepo repo = new PostRepo();

        public List<Post> GetAllPosts()
        {
            return repo.GetAllPosts().OrderByDescending(p => p.PublishedDate).ToList();
        }

        public List<Category> GetAllCategories()
        {
            return repo.GetAllCategories();
        }

        public int CreateCategoryIfNew(Category category)
        {
            int id;

            try
            {
                id = repo.GetCategoryIdByName(category.CategoryName);
            }
            catch (Exception ex)
            {
                return 0;
            }

            if (id != 0)
            {
                return id;
            }

            try
            {
                int result = repo.CreateCategory(category);
                return result;
            }
            catch (Exception ex)
            {
                return 0;
            }
        }

        public List<Tag> GetAllTags()
        {
            return repo.GetAllTags();
        }


        public Post GetPostById(int? id)
        {
            try
            {
                var result = repo.GetPostById(id);
                return result;
            }
            catch (Exception ex)
            {
                return null;
            }
        }

        public Post EditPost(Post post)
        {
            try
            {
                var result = repo.EditPost(post);
                return result;
            }
            catch (Exception ex)
            {
                return null;
            }
        }

        public void DeletePost(int? id)
        {
            repo.DeletePost(id);
        }

        public int CreatePost(Post post)
        {
            try
            {
                int result = repo.CreatePost(post);
                return result;
            }
            catch (Exception ex)
            {
                return 0;
            }

        }

        public List<string> ParseTagList(string tagsWritten)
        {
            return tagsWritten.Split('#').Select(t => t.Trim()).ToList();
        }

        public List<Tag> TagHandler(string tagsWritten)
        {
            List<string> tagStrings = ParseTagList(tagsWritten);

            List<Tag> tags = new List<Tag>();

            foreach (var t in tagStrings)
            { 
                //Find out if the tag already exists, if so get its ID. If not, create it and get its ID.
                int id;

                try
                {
                   id = repo.GetTagIdByName(t);
                }
                catch (Exception ex)
                {
                    return null;
                }

                Tag tag = new Tag();
                tag.TagName = t;

                if (id == 0)
                {
                    try
                    {
                        //maybe trouble
                        tag.TagId = repo.CreateTag(tag);
                    }
                    catch (Exception ex)
                    {
                        return null;
                    }
                }
                else
                {
                    tag.TagId = id;
                }

                tags.Add(tag);
            }

            return tags;
        } 

        public List<Status> GetAllStatuses()
        {
            var result = repo.GetAllStatuses();
            return result;
        }
    }
}
