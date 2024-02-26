using System;
using System.Collections.Generic;
using System.Text;
using System.IO;

// если не помните про реализацию метода цепочек в Dictionary в C#
// https://blog.markvincze.com/back-to-basics-dictionary-part-2-net-implementation/

internal class Program
{
	class Dict<TKey,TValue>
	{
		private struct Entry
		{
			public int hashCode;    // Lower 31 bits of hash code, -1 if unused
			public int next;        // Index of next entry, -1 if last
			public TKey key;        // Key of entry
			public TValue value;    // Value of entry
		}

		private int[] buckets;
		private Entry[] entries;
		private int count;
		private IEqualityComparer<TKey> comparer;

		public Dict()
		{
			this.comparer = EqualityComparer<TKey>.Default;
			Initialize(2);
		}

		public Dict(IEqualityComparer<TKey> cmp)
		{
			this.comparer = cmp;
			Initialize(2);
		}

		public int Count
		{
			get { return count; }
		}

		private void Initialize(int size)
		{
			buckets = new int[size];
			for(int i = 0; i < buckets.Length; i++)
				buckets[i] = -1;
			entries = new Entry[size];
		}
		public void Add(TKey key, TValue value)
		{
			Insert(key, value);
		}
		private void Insert(TKey key, TValue value)
		{
			int hashCode = comparer.GetHashCode(key) & 0x7FFFFFFF;
			int targetBucket = hashCode % buckets.Length;

			for(int i = buckets[targetBucket]; i >= 0; i = entries[i].next)
			{
				if(entries[i].hashCode == hashCode && comparer.Equals(entries[i].key, key))
				{
					entries[i].value = value;
					return;
				}
			}
			int index;

			if(count == entries.Length)
			{
				Resize();
				targetBucket = hashCode % buckets.Length;
			}
			index = count;
			count++;

			entries[index].hashCode = hashCode;
			entries[index].next = buckets[targetBucket];
			entries[index].key = key;
			entries[index].value = value;
			buckets[targetBucket] = index;
		}

		public bool ContainsKey(TKey key)
		{
			return FindEntry(key) >= 0;
		}

		private int FindEntry(TKey key)
		{
			if(key == null)
				return -1;

			if(buckets != null)
			{
				int hashCode = comparer.GetHashCode(key) & 0x7FFFFFFF;
				for(int i = buckets[hashCode % buckets.Length]; i >= 0; i = entries[i].next)
				{
					if(entries[i].hashCode == hashCode && comparer.Equals(entries[i].key, key)) return i;
				}
			}
			return -1;
		}

		public TValue this[TKey key]
		{
			get {
				int i = FindEntry(key);
				if(i >= 0)
					return entries[i].value;
				return
				default(TValue);
			}
			set {
				Insert(key, value);
			}
		}

		private void Resize()
		{
			int newSize = count * 2;
			int[] newBuckets = new int[newSize];
			for(int i = 0; i < newBuckets.Length; i++) newBuckets[i] = -1;
			Entry[] newEntries = new Entry[newSize];
			Array.Copy(entries, 0, newEntries, 0, count);
			for(int i = 0; i < count; i++)
			{
				if(newEntries[i].hashCode >= 0)
				{
					int bucket = newEntries[i].hashCode % newSize;
					newEntries[i].next = newBuckets[bucket];
					newBuckets[bucket] = i;
				}
			}
			buckets = newBuckets;
			entries = newEntries;
		}
	}

	public static int hash(string name)
	{
		int sum = 0;
		foreach(char ch in name)
			sum = (sum * 31) + ch;
		return sum;
	}

	public class SimpleSumComparer : IEqualityComparer<string>
	{
		public bool Equals(string a, string b)
		{
			return a == b;
		}

		public int GetHashCode(string name)
		{
			int hash = 0;
			foreach(char ch in name)
				hash = (hash * 31) + ch;
			return hash;
		}
	}

	public static void Main(string[] args)
	{
		string input_text = System.IO.File.ReadAllText(@"../engwiki_ascii.txt");
		var watch = System.Diagnostics.Stopwatch.StartNew();
		long elapsedMs;

		//var obj = new Dictionary<string, int>(new SimpleSumComparer());
		var obj = new Dict<string, int>(new SimpleSumComparer());

		string str = "";
		foreach(var i in input_text)
		{
			if(i >= 'a' && i <= 'z' || i >= 'A' && i <= 'Z' || i == '\'')
				str += i;
			else if(str.Length > 0)
			{
				if(obj.ContainsKey(str))
					++obj[str];
				else
					obj.Add(str, 1);
				str = "";
			}
		}

		watch.Stop();
		elapsedMs = watch.ElapsedMilliseconds;
		System.Console.WriteLine("time:  " + elapsedMs/1000.0);
		
		Console.WriteLine("wiki: " + obj["wiki"]);
		Console.WriteLine("size: " + obj.Count);
	}
}
