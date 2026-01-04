#ifndef MEDIA_STATS_H_INCLUDED
#define MEDIA_STATS_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

// Add a video or music title with the given total duration.  Return 1
// or 0 on success or failure, respectively.
extern int add_media(const char * title, double duration);

// Add a media viewing of the given title by the given user of a
// segment defined by the given start and finish times.  Return 1 or 0
// on success or failure, respectively.
extern int add_view(const char * title, const char * user,
		    double start, double finish);

// Clear all media titles and therefore all views.
extern void clear_media();

// Clear all media views but keep the media titles.
extern void clear_views();

// Number of unique users who have viewed any portion of the given
// media. Return -1 if the title does not exist.
extern int unique_viewers(const char * title);

// Total time of the given title that the given user has seen at least
// once. Return -1 if the title does not exist.  Return 0 if the user
// does not exist.
extern double total_time_viewed(const char * title, const char * user);

// Number of users who viewed the entire duration of the given media
// file in one or more viewings. Return -1 if the title does not exist.
extern int complete_views(const char * title);

#ifdef __cplusplus
}
#endif

#endif
