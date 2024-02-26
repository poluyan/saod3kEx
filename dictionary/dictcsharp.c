#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int count = 0;
int capacity = 0;

struct Entry
{
	int hashCode;
	int next;
	char* key;
	int value;
};

int GetHashCode(const char *name)
{
	int sum = 0, i = 0;
	for(;name[i] != '\0'; i++)
		sum = (sum * 31) + name[i];
	return sum;
}

void Initialize(int size, int **buckets, struct Entry **entries)
{
	*buckets = (int*)malloc(size*sizeof(int));
	int i;
	for(i = 0; i < size; i++)
		(*buckets)[i] = -1;
	*entries = (struct Entry*)malloc(size*sizeof(struct Entry));
	capacity = size;
}

void Resize(int **buckets, struct Entry **entries)
{
	int newSize = count * 2, i = 0;
	capacity = newSize;
	int* newBuckets = (int*)malloc(newSize*sizeof(int));
	for(i = 0; i < newSize; i++)
		newBuckets[i] = -1;
	struct Entry* newEntries = (struct Entry*)malloc(newSize*sizeof(struct Entry));
	for(i = 0; i < count; i++)
		newEntries[i] = (*entries)[i];
	for(i = 0; i < count; i++)
	{
		if(newEntries[i].hashCode >= 0)
		{
			int bucket = newEntries[i].hashCode % newSize;
			newEntries[i].next = newBuckets[bucket];
			newBuckets[bucket] = i;
		}
	}

	free(*buckets);
	free(*entries);
	*buckets = newBuckets;
	*entries = newEntries;
}

int FindEntry(const char *key, int *buckets, struct Entry *entries)
{
	int hashCode = GetHashCode(key) & 0x7FFFFFFF, i = 0;
	for(i = buckets[hashCode % capacity]; i >= 0; i = entries[i].next)
	{
		if(entries[i].hashCode == hashCode && strcmp(entries[i].key, key) == 0) return i;
	}
	return -1;
}

int ContainsKey(const char *key, int* buckets, struct Entry* entries)
{
	return FindEntry(key, buckets, entries) >= 0 ? 1 : 0;
}

void Insert(const char* key, int value, int **buckets, struct Entry **entries)
{
	int hashCode = GetHashCode(key) & 0x7FFFFFFF, i = 0;
	int targetBucket = hashCode % capacity;

	for(i = (*buckets)[targetBucket]; i >= 0; i = (*entries)[i].next)
	{
		if((*entries)[i].hashCode == hashCode && strcmp((*entries)[i].key, key) == 0)
		{
			(*entries)[i].value = value;
			return;
		}
	}
	int index;

	if(count == capacity)
	{
		Resize(buckets, entries);
		targetBucket = hashCode % capacity;
	}
	index = count;
	count++;

	(*entries)[index].hashCode = hashCode;
	(*entries)[index].next = (*buckets)[targetBucket];

	int key_size = strlen(key);
	(*entries)[index].key = (char*)malloc((key_size + 1)*sizeof(char));
	for(i = 0; i < key_size; i++)
		(*entries)[index].key[i] = key[i];
	(*entries)[index].key[key_size] = '\0';

	(*entries)[index].value = value;
	(*buckets)[targetBucket] = index;
}

void Increment(const char* key, int *buckets, struct Entry **entries)
{
	int i = FindEntry(key, buckets, *entries);
	if(i >= 0)
		++(*entries)[i].value;
}

int GetValue(const char* key, int *buckets, struct Entry *entries)
{
	int i = FindEntry(key, buckets, entries);
	return i >= 0 ? entries[i].value : -1;		
}

int main()
{
	FILE *file = fopen("../engwiki_ascii.txt", "r");
	if(file == NULL)
	{
		printf("error in opening!\n");
		return 0;
	}

	fseek(file, 0, SEEK_END);
	long file_size = ftell(file);
	fseek(file, 0, SEEK_SET);

	char *buffer = (char*)malloc(file_size + 1);
	fread(buffer, 1, file_size, file);
	buffer[file_size] = '\0';
	int text_size = strlen(buffer);

	fclose(file);
	
	clock_t start, end;
	start = clock();
	
	int i, j;
	int* buckets;
	struct Entry* entries;
	Initialize(2, &buckets, &entries);
		
	char str[256];
	for(i = 0, j = 0; i < text_size; i++)
	{
		if((buffer[i] >= 'a' && buffer[i] <= 'z') || (buffer[i] >= 'A' && buffer[i] <= 'Z') || buffer[i] == '\'')
		{
			str[j++] = buffer[i];
		}
		else if(j > 0)
		{
			str[j] = '\0';
			if(ContainsKey(str, buckets, entries) > 0)
				Increment(str, buckets, &entries);
			else
				Insert(str, 1, &buckets, &entries);
			j = 0;
		}
	}
	
	end = clock();
	printf("time: %f seconds\n", ((double)(end - start)) / CLOCKS_PER_SEC);
	
	printf("wiki: %d\n", GetValue("wiki", buckets, entries));
	printf("size: %d\n", count);
	
	free(buffer);

	for(i = 0; i < count; i++)
	{
		if(entries[i].key != NULL)
			free(entries[i].key);
	}
	free(buckets);
	free(entries);
	
	return 0;
}
