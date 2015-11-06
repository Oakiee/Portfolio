using System;
using System.Collections.Generic;
using System.Data.Entity;
using System.Linq;
using System.Runtime.Remoting.Metadata.W3cXsd2001;
using System.Text;
using System.Threading.Tasks;
using CapstoneBlog.Models;

namespace CapstoneBlog.Data
{
    public class PostRepo : IPostRepo
    {
        private EntityAppDbContext.ApplicationDbContext db = new EntityAppDbContext.ApplicationDbContext();

        public void DeletePost(int? id)
        {
            Post post = db.Posts.Find(id);
            db.Posts.Remove(post);
            db.SaveChanges();
        }

        public Post EditPost(Post post)
        {
            db.Entry(post).State = EntityState.Modified;
            db.SaveChanges();

            return post;
        }

        public List<Category> GetAllCategories()
        {
            return db.Categories.ToList();
        }

        public int CreateCategory(Category category)
        {
            db.Categories.Add(category);
            db.SaveChanges();
            
            return category.CategoryId;
        }

        public int GetCategoryIdByName(string categoryName)
        {
            var category = db.Categories.FirstOrDefault(c => c.CategoryName == categoryName);

            if (category == null)
            {
                return 0;
            }

            return category.CategoryId;
        }

        public int CreateTag(Tag tag)
        {
            db.Tags.Add(tag);
            db.SaveChanges();

            return tag.TagId;
        }

        public int GetTagIdByName(string tagName)
        {
            var tag = db.Tags.FirstOrDefault(t => t.TagName == tagName);

            if (tag == null)
            {
                return 0;
            }

            return tag.TagId;
        }


        public List<Post> GetAllPosts()
        {
            return db.Posts.ToList();
        }

        public List<Status> GetAllStatuses()
        {
            return db.Status.ToList();
        }

        public List<Tag> GetAllTags()
        {
            return db.Tags.ToList();
        }

        public Post GetPostById(int? id)
        {
            return db.Posts.FirstOrDefault(p => p.PostId == id);
        }

        public int CreatePost(Post post)
        {
            db.Posts.Add(post);
            db.SaveChanges();
            
            return post.PostId;
        }

    }
}
